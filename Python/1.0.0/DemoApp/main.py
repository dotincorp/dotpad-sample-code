from PySide6.QtWidgets import QApplication, QListWidget, QLineEdit, QPushButton, QMainWindow, QListWidgetItem,  QVBoxLayout, QHBoxLayout,QWidget, QLabel
from PySide6.QtCore import QMetaObject, Slot, Qt
from qasync import QEventLoop
import sys
import asyncio
from SDK import DotPadSDK

class DotPadApp(QMainWindow):
    def __init__(self):
        super().__init__()
        self.sdk = DotPadSDK()  # DotPad SDK 초기화
        self.device = None
        self.setWindowTitle("DotPad Controller")
        self.setGeometry(4100, 100, 300, 200)
    
        # 버튼 추가
        self.initUI()
        QMetaObject.connectSlotsByName(self)

    def initUI(self):
        # define search devices button
        self.button_search = QPushButton("Search to DotPad")
        self.button_search.setObjectName("button_search")
        # define list of devices
        self.device_list_widget = QListWidget()
        self.device_list_widget.setObjectName("device_list_widget")
        # define connect button
        self.button_connect = QPushButton("Connect to DotPad")
        self.button_connect.setObjectName("button_connect")

        self.button_display = QPushButton("Display Graphic Data")
        self.button_display.setObjectName("button_display")
        self.button_text_display = QPushButton("Display Text Data")
        self.button_text_display.setObjectName("button_text_display")
        self.input = QLineEdit()
        self.button_reset = QPushButton("Reset Graphic Data")
        self.button_reset.setObjectName("button_reset")

        self.button_text_reset = QPushButton("Reset Text Graphic Data")
        self.button_text_reset.setObjectName("button_text_reset")

        layout = QVBoxLayout()
        layout.addWidget(self.button_search)
        layout.addWidget(self.device_list_widget)
        layout.addWidget(self.button_connect)
        layout.addWidget(self.button_display)
        layout.addWidget(self.button_text_display)
        layout.addWidget(self.input)    
        layout.addWidget(self.button_reset)
        layout.addWidget(self.button_text_reset)
        keyLayout = QHBoxLayout()
        self.keyLabel = {"LP":QLabel("LP"),"F1":QLabel("F1"),"F2":QLabel("F2"),"F3":QLabel("F3"),"F4":QLabel("F4"),"RP":QLabel("RP")}
        for key, Function in self.keyLabel.items():
            #Qlable 텍스트 중앙정렬
            Function.setAlignment(Qt.AlignCenter)
            keyLayout.addWidget(Function)
        layout.addLayout(keyLayout)
        container = QWidget()
        container.setLayout(layout)
        self.setCentralWidget(container)

        
        
    @Slot()
    def on_button_search_clicked(self):
        async def async_search():
            print("Searching for DotPad devices...")
            self.device_list_widget.clear()
            try:
                self.result = await self.sdk.scan()
                print(f"Found {len(self.result)} devices.")
                # self.device = result[0]
                for device in self.result:
                    self.device_list_widget.addItem(device.name)
            except Exception as e:
                print(f"Error during connection: {e}")


        return asyncio.create_task(async_search())

    @Slot()
    def on_button_connect_clicked(self):
        async def async_connect_device():
            print("Connecting for DotPad devices...")
            try:
                print(type(self.device))
                connected = await self.sdk.connect(self.device)
                if connected:
                    print(f"Connected to {self.device.name}")
                    self.button_connect.setText("Disconnect")
                    await self.add_key_event_listener()
                else:
                    print("Failed to connect.")
            except Exception as e:
                print(f"Error during connection: {e}")

        async def async_disconnect():
            await self.sdk.disconnect(self.device.name)
            self.button_connect.setText("Connect to DotPad")
        if self.sdk.device_map:
            asyncio.create_task(async_disconnect())
        else:
            self.device = self.result[self.device_list_widget.currentRow()]
            asyncio.create_task(async_connect_device())
                
                

    @Slot()
    def on_button_display_clicked(self):
        async def async_display_graphic():
            if self.device:
                print("Displaying graphic data...")
                await self.sdk.display_graphic_data(self.device.name, self.input.text())
        """버튼 클릭 이벤트에서 비동기 작업 실행"""
        asyncio.create_task(async_display_graphic())

    @Slot()
    def on_button_text_display_clicked(self):
        async def async_text_display_graphic():
            if self.device:
                print("Displaying graphic data...")
                await self.sdk.display_text_data(self.device.name, self.input.text())
        """버튼 클릭 이벤트에서 비동기 작업 실행"""
        asyncio.create_task(async_text_display_graphic())

    @Slot()
    def on_button_reset_clicked(self):
        """버튼 클릭 이벤트에서 비동기 작업 실행"""
        async def async_reset_graphic():
            if self.device:
                print("Resetting graphic data...")
                await self.sdk.reset_graphic_data(self.device.name)
        asyncio.create_task(async_reset_graphic())


    @Slot()
    def on_button_text_reset_clicked(self):
        """버튼 클릭 이벤트에서 비동기 작업 실행"""
        async def async_reset_text():
            if self.device:
                print("Resetting text data...")
                await self.sdk.reset_text_data(self.device.name)
        asyncio.create_task(async_reset_text())








    async def add_key_event_listener(self):
        """키 이벤트 리스너 추가"""
        async def key_event_callback(event_code):
            print(f"Key event received: {event_code}")
            for key in event_code["keys"]:
                match event_code["event"]:
                    case "key down":
                        self.keyLabel[key].setEnabled(False)
                    case "key up":
                        if key == "function":
                            self.keyLabel["F1"].setEnabled(True)
                            self.keyLabel["F2"].setEnabled(True)
                            self.keyLabel["F3"].setEnabled(True)
                            self.keyLabel["F4"].setEnabled(True)
                        elif key == "panning":
                            self.keyLabel["LP"].setEnabled(True)
                            self.keyLabel["RP"].setEnabled(True)
                            

        try:
            await self.sdk.add_listener_key_event(self.device.name, key_event_callback)
            print("Key event listener added. Waiting for events...")
        except Exception as e:
            print(f"Error during adding key event listener: {e}")
    




if __name__ == "__main__":
    app = QApplication(sys.argv)
    loop = QEventLoop(app)
    asyncio.set_event_loop(loop)

    mainWindow = DotPadApp()
    mainWindow.show()

    with loop:
        loop.run_forever()
