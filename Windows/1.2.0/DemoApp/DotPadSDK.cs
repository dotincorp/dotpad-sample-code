using System.Text;
using System.Runtime.InteropServices;
using static demo.app.MainForm;
using System;

namespace demo.app
{
    // 기기명 가져오는 콜백 델리게이트 정의
    public delegate void DeviceNameCallback(IntPtr deviceName);

    public class DotPadSDK
    {
        [DllImport("DotPadSDK-1.2.0.dll")]
        public static extern DOT_PAD_SDK_ERROR DOT_PAD_INIT(int portNumber);

        [DllImport("DotPadSDK-1.2.0.dll")]
        public static extern DOT_PAD_SDK_ERROR DOT_PAD_INIT_WITH_DEVICE_TYPE(int portNumber, int deviceType);

        [DllImport("DotPadSDK-1.2.0.dll")]
        public static extern DOT_PAD_SDK_ERROR DOT_PAD_DEINIT();

        // 디바이스명 조회
        [DllImport("DotPadSDK-1.2.0.dll")]
        public static extern DOT_PAD_SDK_ERROR DOT_PAD_GET_DEVICE_NAME(DeviceNameCallback callback);

        // 펌웨어 버전 조회
        [DllImport("DotPadSDK-1.2.0.dll")]
        public static extern DOT_PAD_SDK_ERROR DOT_PAD_GET_FW_VERSION(StringBuilder FWVersion);

        // 20셀 점자 표시
        [DllImport("DotPadSDK-1.2.0.dll", CharSet = CharSet.Unicode)]
        public static extern DOT_PAD_SDK_ERROR DOT_PAD_BRAILLE_DISPLAY(StringBuilder input, int language);

        [DllImport("DotPadSDK-1.2.0.dll")]
        public static extern DOT_PAD_SDK_ERROR DOT_PAD_DISPLAY_DATA(byte[] data, int len);

        [DllImport("DotPadSDK-1.2.0.dll")]
        public static extern DOT_PAD_SDK_ERROR DOT_PAD_DISPLAY(string filePath);

        // 그래픽영역 초기화
        [DllImport("DotPadSDK-1.2.0.dll")]
        public static extern DOT_PAD_SDK_ERROR DOT_PAD_RESET_DISPLAY();

        // 점역영역 초기화
        [DllImport("DotPadSDK-1.2.0.dll")]
        public static extern DOT_PAD_SDK_ERROR DOT_PAD_RESET_BRAILLE_DISPLAY();

        // 펑션키, 패닝키 콜백받는 함수
        [DllImport("DotPadSDK-1.2.0.dll")]
        public static extern DOT_PAD_SDK_ERROR DOT_PAD_REGISTER_KEY_CALLBACK(KeyPressCallbackFunc keyPressCallback);

        // 이전,다음키 전송 처리
        [DllImport("DotPadSDK-1.2.0.dll")]
        public static extern DOT_PAD_SDK_ERROR DOT_PAD_SEND_KEY(int keyCode);

    }
}
