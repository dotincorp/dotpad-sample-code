import { useEffect, useRef, useState } from 'react';
import { DotPadSDK, DotPadSample } from "./DotPadSDK-1.0.0-min"
import "./App.css";

export default function DotPad() 
{
  interface Device {
    target: null;
    name: string;
    connected: boolean;
  }

  const dotpadsdk = useRef<DotPadSDK>();
  const [devices, setDevices] = useState<Device[]>([]);

  useEffect(() => 
  {
    dotpadsdk.current = new DotPadSDK();
  }, []);

  // 닷패드 연결정보 갱신
  const updateDeviceConnection = async (device: any, connected: any) => 
  {
    // (1) 닷패드 연결/해제 처리
    if (connected) {
      const connected = await dotpadsdk.current?.connect(device.target);
      if (connected) {
        await dotpadsdk.current?.addListenerNotification(device.target, notificationCallback);
      }
    } else {
      await dotpadsdk.current?.disconnect(device.target);
    }
    // (2) 닷패드 연결상태 갱신
    setDevices(devices => devices.map(d => d.name === device.name ? { ...d, connected } : d));
  };

  // 닷패드 선택
  const handleSelectDevice = async () => 
  {
    const device = await dotpadsdk.current?.request();
    const deviceInfo = {
      target: device,
      name: device.name,
      connected: false
    };
    setDevices(currentDevices => [...currentDevices, deviceInfo]);
  };

  // 닷패드 출력
  const handlePrintDevice = async () => 
  {
    devices.map(async (device) => {
      await dotpadsdk.current?.print(device, DotPadSample.SAMPLE2, "graphic");
    });
  };

  // 닷패드 펑션키 콜백처리
  const notificationCallback = async () => 
  {
    console.log("**** notificationCallback ****");
  }

  return (
      <div className="tableContainer">
        <div className="buttonContainer">
          <button className="selectButton" onClick={handleSelectDevice}>
            닷패드 선택
          </button>
          <button className="printButton" onClick={handlePrintDevice}>
            닷패드 출력
          </button>
        </div>
        <table className="table">
          <thead>
            <tr>
              <th className="header">닷패드 이름</th>
              <th className="header">액션</th>
            </tr>
          </thead>
          <tbody>
            {devices.map((device) => (
              <tr key={device.name} className="row">
                <td className="cell">{device.name}</td>
                <td className="cell">
                  {!device.connected && (
                    <button className="button" onClick={() => updateDeviceConnection(device, true)}>
                      연결
                    </button>
                  )}
                  {device.connected && (
                    <button className="button" onClick={() => updateDeviceConnection(device, false)}>
                      해제
                    </button>
                  )}
                </td>
              </tr>
            ))}
          </tbody>
        </table>
      </div>
  );
}
