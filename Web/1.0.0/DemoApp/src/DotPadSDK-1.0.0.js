// ============================================================================
// DotPadSDK
// ============================================================================
class DotPadSDK {
  /**
   * 디바이스맵 전역변수
   * key : 디바이스명
   * value : {service, characteristic}
   */
  static deviceMap = new Map();

  // 생성자
  constructor() {
    this.DOTPAD_PREFIX = "DotPad";
    this.DOTPAD_SERVICE = "49535343-fe7d-4ae5-8fa9-9fafd205e455";
    this.DOTPAD_CHARACTERISTIC = "49535343-1e4d-4bd9-ba61-23c647249616";
    this.ACK_PATTERN = /aa550006(..)0201(..)00.*/;
    this.NOTI_PATTERN = /aa550006(..)0202(..)00.*/;
  }

  // --------------------------------------------------------------------------
  // 닷패드 기기 요청 
  // --------------------------------------------------------------------------
  async request() {
    const bluetoothOption = {
      filters: [{ namePrefix: this.DOTPAD_PREFIX }],
      optionalServices: [this.DOTPAD_SERVICE]
    };
    return await navigator.bluetooth.requestDevice(bluetoothOption);
  }

  // --------------------------------------------------------------------------
  // 닷패드 기기 연결
  // @device : 닷패드 디바이스
  // --------------------------------------------------------------------------
  async connect(device) {
    if (!device) throw new Error('No Bluetooth device selected');
    const server = await device.gatt.connect();
    const service = await device.gatt.getPrimaryService(this.DOTPAD_SERVICE);
    const characteristic = await service.getCharacteristic(this.DOTPAD_CHARACTERISTIC);

    const deviceName = server.device.name;
    DotPadSDK.deviceMap.set(deviceName, { service, characteristic });
    return server.connected;
  }

  // --------------------------------------------------------------------------
  // 닷패드 기기 연결 끊기
  // @device : 닷패드 디바이스
  // --------------------------------------------------------------------------
  async disconnect(device) {
    if (DotPadSDK.deviceMap.has(device)) {
      DotPadSDK.deviceMap.delete(device);
    }
    return device.gatt.disconnect();
  }

  // --------------------------------------------------------------------------
  // 그래픽영역(300셀) 전체 출력
  // @device : 닷패드 디바이스
  // @hexData : 그래픽 헥사 데이타
  // --------------------------------------------------------------------------
  async displayGraphicData(device, hexData) {
    this.displayFullData(device, hexData, "graphic");
  }

  // --------------------------------------------------------------------------
  // 그래픽영역(300셀) 라인별 출력
  // @device : 닷패드 디바이스
  // @lineId : 라인 아이디 (1~10)
  // @cellIndex : 셀 인덱스 (0~29)
  // @hexData : 그래픽 헥사 데이타
  // --------------------------------------------------------------------------
  async displayGraphicLineData(device, lineId, cellIndex, hexData) {
    this.displayLineData(device, lineId, cellIndex, hexData, "graphic");
  }  

  // --------------------------------------------------------------------------
  // 그래픽 영역(300셀) 전체 초기화
  // @device : 닷패드 디바이스
  // --------------------------------------------------------------------------
  async resetGraphicData(device) {
    const resetHexData = DotPadData.getResetData(300);
    this.displayGraphicData(device, resetHexData);
  }
 
  // --------------------------------------------------------------------------
  // 텍스트영역(20셀) 점자 출력
  // @device : 닷패드 디바이스
  // @hexData : 점자 헥사 데이타
  // --------------------------------------------------------------------------
  async displayTextData(device, hexData) {
    const deviceInfo = DotPadSDK.deviceMap.get(device.name);
    if (deviceInfo && deviceInfo.characteristic) {
      // (1) 점역 헥사 데이타 워드랩 설정 처리
      const wrap = new BrailleWordWrap(20, hexData);
      const wrapHexList = wrap.toWrappHex();
      DotPadSendModule.setBrailleWordWrapList(wrapHexList);
      // (2) 점역 데이타 전송 처리
      DotPadSendModule.sendBrailleWordWrap(deviceInfo.characteristic, 1)
    } else {
      console.error('Device is not connected or characteristic not found');
    }
  }

  // --------------------------------------------------------------------------
  // 텍스트 영역(20셀) 전체 초기화
  // @device : 닷패드 디바이스
  // --------------------------------------------------------------------------
  async resetTextData(device) {
    const deviceInfo = DotPadSDK.deviceMap.get(device.name);
    if (deviceInfo && deviceInfo.characteristic) {
      const resetHexData = DotPadData.getResetData(20);
      const resetCommandData = DotPadData.getRequestLineData(0, 0, resetHexData, true);
      await deviceInfo.characteristic.writeValue(resetCommandData);
    } else {
      console.error('Device is not connected or characteristic not found');
    }
  }

  // --------------------------------------------------------------------------
  // 모드에 따른 그래픽영역(300셀) 전체 출력
  // @device : 닷패드 디바이스
  // @hexData : 출력할 헥사 데이타
  // @mode : graphic(그래픽모드), text(텍스트모드)
  // --------------------------------------------------------------------------
  async displayFullData(device, hexData, mode) {
    const deviceInfo = DotPadSDK.deviceMap.get(device.name);
    if (deviceInfo && deviceInfo.characteristic) {
      // (1) 분할 데이타 생성
      let commandByteChunkList = [];
      if (mode === "graphic") {
        commandByteChunkList = DotPadData.getRequestData(hexData, false);
      } else if (mode === "text") {
        commandByteChunkList = DotPadData.getRequestData(hexData, true);
      }
      // (2) 라인별로 분할해서 데이타 전송 처리
      let lineId = 1;
      for (let commandByteChunk of commandByteChunkList) {
        // 전송 모듈에 데이타 설정
        DotPadSendModule.setSendData(lineId++, commandByteChunk, false);
      }
      // 다음 라인 전송 요청
      await DotPadSendModule.sendNextLine(deviceInfo.characteristic);
    } else {
      console.error('Device is not connected or characteristic not found');
    }
  }

  // --------------------------------------------------------------------------
  // 영역 라인별 부분 출력
  // @device : 닷패드 디바이스
  // @lineId : 라인 아이디 (1~10)
  // @cellIndex : 셀 인덱스 (0~29)
  // @hexData : 출력할 헥사 데이타
  // @mode : 출력모드 (graphic, text)
  // --------------------------------------------------------------------------
  async displayLineData(device, lineId, cellIndex, hexData, mode) {
    const deviceInfo = DotPadSDK.deviceMap.get(device.name);
    if (deviceInfo && deviceInfo.characteristic) {
      let commandByteData = null;
      if (mode === "graphic") {
        commandByteData = DotPadData.getRequestLineData(lineId, cellIndex, hexData, false);
      } else if (mode === "text") {
        commandByteData = DotPadData.getRequestLineData(lineId, cellIndex, hexData, true);
      }
      DotPadSendModule.setSendData(lineId, commandByteData, false);
      await DotPadSendModule.sendNextLine(deviceInfo.characteristic);
    } else {
      console.error('Device is not connected or characteristic not found');
    }
  }
  
  // --------------------------------------------------------------------------
  // 닷패드 펑션키 콜백 수신 처리 
  // @device : 닷패드 디바이스
  // @callbackFunction : 펑션키 콜백함수
  // --------------------------------------------------------------------------
  async addListenerKeyEvent(device, callbackFunction) {
    if (!device) throw new Error('No Bluetooth device connected');
    const deviceInfo = DotPadSDK.deviceMap.get(device.name);

    deviceInfo.characteristic.startNotifications().then(() => {
      deviceInfo.characteristic.addEventListener('characteristicvaluechanged', async (event) => {
        const notify = new DotPadNotifyModule(event, deviceInfo.characteristic);
        // (1) ACK 정보 처리
        notify.setAckProcess();
        // (2) 패닝키 이벤트 처리
        notify.setPanningKeyEvent(callbackFunction);
        // (3) 펑션키 이벤트 처리
        notify.setFunctionKeyEvent(callbackFunction);
      });
    });
  }
}

// ============================================================================
// DotPadNotifyModule
// ============================================================================
class DotPadNotifyModule {
  /** 
   * 생성자
   * @param {object} event 
   */
  constructor(event, characteristic) {
    this.ACK_PATTERN = /aa550006(..)0201(..)00.*/;
    this.NOTI_PATTERN = /aa550006(..)0202(..)00.*/;
    this.PANNING_KEY = "aa55000900031200";
    this.FUNCTION_KEY = "aa55000900033200";

    this.characteristic = characteristic;    
    this.receiveHexPacket = Array.from(new Uint8Array(event.target.value.buffer))
                            .map(b => b.toString(16).padStart(2, '0'))
                            .join('');
  }

  /**
   * ACK 정보수신 후 처리
   */
  async setAckProcess() {
    const ackPacket = this.receiveHexPacket.match(this.ACK_PATTERN);
    if (ackPacket) {
      const ackLineId = parseInt(ackPacket[1], 16);
      DotPadSendModule.setAckData(ackLineId, true);
      await DotPadSendModule.sendNextLine(this.characteristic);
    }
  }

  /**
   * 패닝키 이벤트 처리
   */
  setPanningKeyEvent(callbackFunction) {
    if (this.receiveHexPacket.startsWith(this.PANNING_KEY)) {
      const keyData = parseInt(this.receiveHexPacket.slice(19, 20), 16);
      let pageNo = DotPadSendModule.wordWrapPageNo;
      let pageSize = DotPadSendModule.sendWordWrapList.length;

      if (keyData === 4) { // 이전
        // 20셀 점역 이전 페이징 처리
        if (pageNo > 0 && pageSize > 0) {
          let prevPageNo = pageNo > 1 ? --pageNo : pageNo;
          DotPadSendModule.sendBrailleWordWrap(this.characteristic, prevPageNo);
        }
        callbackFunction("P1");
      } else if (keyData === 2) { // 다음
        // 20셀 점역 다음 페이징 처리
        if (pageNo > 0 && pageSize > 0) {
          let nextPageNo = pageNo < pageSize ? ++pageNo : pageNo;
          DotPadSendModule.sendBrailleWordWrap(this.characteristic, nextPageNo);
        }
        callbackFunction("P2");
      }
    }
  }

  /**
   * 펑션키 이벤트 처리
   */
  setFunctionKeyEvent(callbackFunction) {
    if (this.receiveHexPacket.startsWith(this.FUNCTION_KEY)) {
      const keyData = parseInt(this.receiveHexPacket.slice(16, 16 + 1), 16);
      if (keyData === 8) { // 1번
        callbackFunction("F1");
      } else if (keyData === 4) { // 2번
        callbackFunction("F2");
      } else if (keyData === 2) { // 3번
        callbackFunction("F3");
      } else if (keyData === 1) { // 4번
        callbackFunction("F4");
      }
    }  
  }
}

// ============================================================================
// DotPadSDK SEND
// ============================================================================
class DotPadSendModule {
  // (전역변수) 닷패드 전송 데이타 버퍼 Map
  // key: lineId, value: {commandData, isAck}
  static sendMapData = new Map();
  // (전역변수) 닷패드 전송 데이타 점역 결과 워드랩 목록
  static sendWordWrapList = [];
  // (전역변수) 점역 워드랩 현재 페이지
  static wordWrapPageNo = -1;

  /**
   * 점역결과 워드랩 배열 데이타 설정
   * @param {Array<string>} brailleWordWrapList 
   */
  static setBrailleWordWrapList(sendWordWrapList) {
    this.sendWordWrapList = []; // 배열 데이타 초기화
    for (let i = 0; i < sendWordWrapList.length; i++) {
      const sendWordWrap = sendWordWrapList[i];
      const commandData = DotPadData.getRequestLineData(0, 0, sendWordWrap, true);
      this.sendWordWrapList.push(commandData);
    }
    this.wordWrapPageNo = -1;
  }

  /**
   * 점역결과 데이타 전송
   * @param {Object} characteristic 
   * @param {number} pageIndex 
   */
  static async sendBrailleWordWrap(characteristic, pageNo) {
    this.wordWrapPageNo = pageNo;
    const commandData = this.sendWordWrapList[pageNo - 1];
    await characteristic.writeValue(commandData);
  }

  /**
   * 전송 데이터 설정
   * @param {number} lineId - 데이터가 전송될 라인의 ID
   * @param {Uint8Array} commandData - 전송될 커맨드 바이트 데이터
   * @param {Boolean} isAck - ACK 수신여부
   * @param {Boolean} isSend - 전송 여부
   */
  static setSendData(lineId, commandData, isAck) {
    this.sendMapData.set(lineId, {
      "commandData": commandData,
      "isAck": isAck
    });
  }

  /**
   * ACK 여부 설정
   * @param {number} lineId - 라인 아이디
   * @param {boolean} isAck - ACK 수신 여부
   */
  static setAckData(lineId, isAck) {
    
    let lineData = this.sendMapData.get(lineId);
    if (lineData) {
      lineData.isAck = isAck;
    }
  }

  /**
   * 다음 데이타 전송 처리
   */
  static async sendNextLine(characteristic) {
    let nextLineId = this.getNextLineId();
    if (nextLineId > -1) {
      let nextLineData = DotPadSendModule.sendMapData.get(nextLineId);
      if (nextLineData) {
        await characteristic.writeValue(nextLineData.commandData);
        //console.log("nextLineId => " + nextLineId);
      }
    }
  }

  /**
   * 다음 라인 ID 조회
   * @returns 
   */
  static getNextLineId() {
    let result = -1;
    for (let key of this.sendMapData.keys()) {
      const isAck = this.sendMapData.get(key).isAck;
      if (isAck === false) {
        result = key;
        break;
      }
    }
    return result;
  }
}

// ============================================================================
// DotPadData
// ============================================================================
class DotPadData {
  // --------------------------------------------------------------------------
  // 초기화 데이타 생성
  // --------------------------------------------------------------------------
  static getResetData(length) {
    return Array(length).fill("00").join("");
  }

  // --------------------------------------------------------------------------
  // 전체 요청 데이타
  // --------------------------------------------------------------------------
  static getRequestData(hexData, isText) {
    const inputBytes = DotDataUtil.hexToBytes(hexData);

    // 1라인이 30셀이라 30bytes로 분할 처리
    const requestChunkList = this._getRequestDataChunkList(inputBytes,  30); 
    const commandChunkList = this._getCommandChunkList(requestChunkList, isText);

    return commandChunkList;
  }

  // --------------------------------------------------------------------------
  // 라인별 요청 데이타
  // --------------------------------------------------------------------------
  static getRequestLineData(lineId, cellIndex, hexData, isText) {
    const inputBytes = DotDataUtil.hexToBytes(hexData);
    const commandChunk = this._getCommandChunkLine(lineId, cellIndex, inputBytes, isText);
    return commandChunk;
  }

  // --------------------------------------------------------------------------
  // 전체 요청 데이타 분할 목록 조회
  // --------------------------------------------------------------------------
  static _getRequestDataChunkList(inputData, chunkSize) {
    const result = [];
    const len = inputData.length;
    for (let i = 0; i < len; i += chunkSize) {
      const size = i + chunkSize;
      const chunk = inputData.slice(i, size > len ? len : size);
      result.push(chunk);
    }
    return result;
  }

  // --------------------------------------------------------------------------
  // 전체 커맨드 명령어 목록 조회
  // --------------------------------------------------------------------------
  static _getCommandChunkList(byteChunkList, isText) {
    let result = [];
    let line = 1;
    for (const dataChunk of byteChunkList) {
      const bytesData = this._getCommandChunkLine(line, 0, dataChunk, isText);
      result.push(bytesData);
      line++;
    }
    return result;
  }

  // --------------------------------------------------------------------------
  // 라인별 커맨드 명령어 조회
  // --------------------------------------------------------------------------
  static _getCommandChunkLine(lineId, cellIndex, byteData, isText) {
    const hexList = [
      ...DotPadProtocol.getSync(),
      ...DotPadProtocol.getLength(byteData),
      ...DotPadProtocol.getDestId(lineId),
      ...DotPadProtocol.getCommandType(),
      ...DotPadProtocol.getDisplayMode(isText),
      ...DotPadProtocol.getStartCell(cellIndex),
      ...DotPadProtocol.getDataBody(byteData),
      DotPadProtocol.getCheckSum(
        DotPadProtocol.getDestId(lineId), 
        DotPadProtocol.getCommandType(),
        DotPadProtocol.getDisplayMode(isText), 
        DotPadProtocol.getStartCell(cellIndex),
        DotPadProtocol.getDataBody(byteData)
      )
    ];
    const bytesData = DotDataUtil.hexToBytes(hexList.join(''));
    return bytesData;
  }
}

// ============================================================================
// DotPadProtocol
// ============================================================================
class DotPadProtocol {
  static getSync() {
    return ["AA", "55"];
  }

  static getLength(data) {
    return ["00", DotDataUtil.decimalToHex(data.length + 6)];
  }

  static getDestId(destId) {
    return [DotDataUtil.decimalToHex(destId)];
  }

  static getCommandType() {
    return ["02", "00"];
  }

  static getDisplayMode(isText) {
    // 0x00 (graphic), 0x80 (text)
    if (isText) {
      return ["80"];
    } else {
      return ["00"];
    }
  }

  static getStartCell(cellIndex) {
    let hexIndex = DotDataUtil.decimalToHex(cellIndex);
    return [hexIndex];
  }

  static getDataBody(data) {
    return DotDataUtil.bytesToHexList(data);
  }

  // --------------------------------------------------------------------------
  // 데이타 유효성 검증
  // --------------------------------------------------------------------------
  static getCheckSum(destId, reqCmd, mode, startCell, dataBody) {
    const checkDataList = [...destId, ...reqCmd, ...mode, ...startCell, ...dataBody];
    let checkSum = 0xA5;
    for (const checkData of checkDataList) {
      checkSum ^= parseInt(checkData, 16);
    }
    return DotDataUtil.decimalToHex(checkSum);
  }
}

// ============================================================================
// DotDataUtil
// ============================================================================
class DotDataUtil {
  // --------------------------------------------------------------------------
  // 바이트 배열을 헥사 문자열로 변환
  // --------------------------------------------------------------------------
  static bytesToHex(bytes) {
    return Array.from(bytes, byte => byte.toString(16).padStart(2, '0')).join('');
  }

  // --------------------------------------------------------------------------
  // 바이트 배열을 헥사 문자열 목록으로 변환
  // --------------------------------------------------------------------------
  static bytesToHexList(bytes) {
    return Array.from(bytes, byte => byte.toString(16).padStart(2, '0'));
  }

  // --------------------------------------------------------------------------
  // 숫자를 헥사 문자열로 변환
  // -------------------------------------------------------------------------- 
  static decimalToHex(data) {
    return Number(data).toString(16).padStart(2, '0');
  }
  
  // --------------------------------------------------------------------------
  // 헥사 문자열을 바이트 배열로 변환
  // --------------------------------------------------------------------------
  static hexToBytes(hexString) {
    if (hexString.length % 2 !== 0) {
        throw new Error('Odd number of hex digits');
    }
    const length = hexString.length / 2;
    const result = new Uint8Array(length);
    for (let i = 0; i < length; i++) {
        const x = parseInt(hexString.substring(i * 2, i * 2 + 2), 16);
        if (isNaN(x)) {
            throw new Error('Expected hex string');
        }
        result[i] = x;
    }
    return result;
  }
}

// ============================================================================
// BrailleWordWrap
// ============================================================================
class BrailleWordWrap {
  static DOUBLE_ZERO = "00"; // 상수로 "00" 문자열 정의, 점자 데이터 분할 기준

  constructor(cellSize, brailleHexData) {
      this.cellSizeHex = cellSize * 2; // 셀 크기를 헥사 값으로 변환 (1셀 = 2 헥사자)
      this.brailleHexData = brailleHexData;
  }

  // 점자 헥사 데이터를 처리하여 결과 문자열 반환
  toWrappHex() {
      let processedData = this.processHexData(); // 원본 데이터를 처리
      let wrappedHexList = this.generateWrappedHexList(processedData); // 처리된 데이터를 셀 크기에 맞게 래핑
      //return this.addSpacesBetweenEveryTwoCharacters(wrappedHexList); // 결과 데이터 사이에 공백 추가
      return wrappedHexList; // 결과 데이터 사이에 공백 추가
  }

  // 점자 데이터를 "00" 기준으로 분할하고 재처리
  processHexData() {
      let endsWithDoubleZero = this.brailleHexData.trim().endsWith(BrailleWordWrap.DOUBLE_ZERO); // 데이터가 "00"으로 끝나는지 확인
      let splitData = this.brailleHexData.split(BrailleWordWrap.DOUBLE_ZERO); // "00"을 기준으로 데이터 분할
      let processedData = [];

      // 분할된 데이터에서 모든 공백 제거 후 "00" 추가
      for (let i = 0; i < splitData.length; i++) {
          processedData[i] = splitData[i].replace(/\s+/g, "") + BrailleWordWrap.DOUBLE_ZERO;
      }

      // 데이터가 원래 "00"으로 끝나지 않았다면 마지막 "00" 제거
      if (!endsWithDoubleZero && processedData.length > 0) {
          let lastItemIndex = processedData.length - 1;
          processedData[lastItemIndex] = this.removeTrailingDoubleZero(processedData[lastItemIndex]);
      }

      return processedData;
  }

  // 처리된 점자 데이터를 셀 크기에 맞게 래핑
  generateWrappedHexList(processedData) {
      let result = [];
      let currentSegment = [];

      // 각 데이터 아이템을 처리하여 적절히 래핑
      for (let dataItem of processedData) {
          this.appendDataToSegment(dataItem, currentSegment, result);
      }

      // 마지막 세그먼트 처리
      if (currentSegment.length > 0) {
          result.push(this.padSegment(currentSegment.join('')));
      }

      return result;
  }

  // 데이터 세그먼트를 적절히 처리하여 결과 리스트에 추가
  appendDataToSegment(dataItem, currentSegment, result) {
      let newLength = currentSegment.join('').length + dataItem.length;
      if (newLength <= this.cellSizeHex) {
          currentSegment.push(dataItem);
      } else {
          if (currentSegment.length > 0) {
              result.push(this.padSegment(currentSegment.join('')));
          }
          currentSegment.length = 0; // 세그먼트 초기화
          currentSegment.push(dataItem);
      }
  }

  // 세그먼트의 남은 공간을 '0'으로 채움
  padSegment(segment) {
      while (segment.length < this.cellSizeHex) {
          segment += '0';
      }
      return segment;
  }

  // 세그먼트의 끝에서 "00" 제거
  removeTrailingDoubleZero(data) {
      return data.substring(0, data.length - 2);
  }

  // 결과 문자열의 각 두 문자 사이에 공백 추가
  addSpacesBetweenEveryTwoCharacters(hexList) {
      let combinedString = hexList.join('');
      let result = [];

      for (let i = 0; i < combinedString.length; i += 2) {
          if (i > 0) {
              result.push(" ");
          }
          result.push(combinedString.substring(i, Math.min(i + 2, combinedString.length)));
      }

      return result.join('');
  }
}

export {
  DotPadSDK
};
