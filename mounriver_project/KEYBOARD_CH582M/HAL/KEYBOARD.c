/********************************** (C) COPYRIGHT *******************************
 * File Name          : KEYBOARD.c
 * Author             : ChnMasterOG
 * Version            : V2.0
 * Date               : 2022/12/1
 * Description        : 机械键盘驱动源文件
 * Copyright (c) 2023 ChnMasterOG
 * SPDX-License-Identifier: GPL-3.0
 *******************************************************************************/

#include "HAL.h"
#include "snake.h"

const uint32_t Row_Pin[ROW_SIZE] = {GPIO_Pin_6, GPIO_Pin_5, GPIO_Pin_3, GPIO_Pin_2, GPIO_Pin_1, GPIO_Pin_0};   //row 6 - 其它键盘布局需修改此处
const uint32_t Colum_Pin[COL_SIZE] = {GPIO_Pin_4, GPIO_Pin_5, GPIO_Pin_6, GPIO_Pin_0, GPIO_Pin_1, GPIO_Pin_2, GPIO_Pin_3,
                                      GPIO_Pin_15, GPIO_Pin_14, GPIO_Pin_13, GPIO_Pin_12, GPIO_Pin_11, GPIO_Pin_9, GPIO_Pin_7};   //colum 14 - 其它键盘布局需修改此处
//row*colum = 6*14 = 84
const uint8_t KeyArrary[ROW_SIZE][COL_SIZE] = {
          //---- COL 0 ----|-- COL 1 --|-- COL 2 --|--- COL 3 ---|--- COL 4 ---|--- COL 5 ---|- COL 6 -|--- COL 7 ---|--- COL 8 ---|--- COL 9 ---|---- COL10 ----|---- COL11 ----|---- COL12 ----|---- COL13 ----|
/* ROW0 */{ KEY_ESCAPE,     KEY_F1,     KEY_F2,     KEY_F3,       KEY_F4,       KEY_F5,       KEY_F6,   KEY_F7,       KEY_F8,       KEY_F9,       KEY_F10,        KEY_F11,        KEY_F12,        KEY_Delete    },
/* ROW1 */{ KEY_GraveAccent,KEY_1,      KEY_2,      KEY_3,        KEY_4,        KEY_5,        KEY_6,    KEY_7,        KEY_8,        KEY_9,        KEY_0,          KEY_Subtraction,KEY_Equal,      KEY_BACKSPACE },
/* ROW2 */{ KEY_TAB,        KEY_Q,      KEY_W,      KEY_E,        KEY_R,        KEY_T,        KEY_Y,    KEY_U,        KEY_I,        KEY_O,        KEY_P,          KEY_LSbrackets, KEY_RSbrackets, KEY_NonUS_WS  },
/* ROW3 */{ KEY_CapsLock,   KEY_A,      KEY_S,      KEY_D,        KEY_F,        KEY_G,        KEY_H,    KEY_J,        KEY_K,        KEY_L,        KEY_Semicolon,  KEY_Quotation,  KEY_ENTER,      KEY_PageUp    },
/* ROW4 */{ KEY_LeftShift,  KEY_None,   KEY_Z,      KEY_X,        KEY_C,        KEY_V,        KEY_B,    KEY_N,        KEY_M,        KEY_Comma,    KEY_FullStop,   KEY_Slash,      KEY_RightShift, KEY_PageDown  },
/* ROW5 */{ KEY_LeftCTRL,   KEY_LeftGUI,KEY_LeftAlt,KEY_SPACEBAR, KEY_SPACEBAR, KEY_RightAlt, KEY_Fn,   KEY_RightCTRL,KEY_LeftArrow,KEY_DownArrow,KEY_RightArrow, KEY_UpArrow,    KEY_End,        KEY_Home      },
};  // 默认键盘布局 - 其它键盘布局需修改此处
const uint8_t Extra_KeyArrary[ROW_SIZE][COL_SIZE] = {
          //-- COL 0 --|--- COL 1 ---|--- COL 2 ---|---- COL 3 ----|--- COL 4 ---|--- COL 5 ---|- COL 6 -|- COL 7 -|- COL 8 -|- COL 9 -|---- COL10 ----|- COL11 -|- COL12 -|-- COL13 --|
/* ROW0 */{ KEY_None,   KEY_None,     KEY_None,     KEY_None,       KEY_None,     KEY_None,     KEY_None, KEY_None, KEY_None, KEY_None, KEY_None,       KEY_None, KEY_None, KEY_None  },
/* ROW1 */{ KEY_None,   KEY_None,     KEY_None,     KEY_None,       KEY_None,     KEY_None,     KEY_None, KEY_None, KEY_None, KEY_None, KEY_None,       KEY_None, KEY_None, KEY_None  },
/* ROW2 */{ KEY_None,   KEY_BACKSPACE,KEY_UpArrow,  KEY_ENTER,      KEY_PageUp,   KEY_None,     KEY_None, KEY_None, KEY_None, KEY_None, KEY_PrintScreen,KEY_None, KEY_None, KEY_None  },
/* ROW3 */{ KEY_None,   KEY_LeftArrow,KEY_DownArrow,KEY_RightArrow, KEY_PageDown, KEY_None,     KEY_None, KEY_None, KEY_None, KEY_None, KEY_None,       KEY_None, KEY_None, KEY_None  },
/* ROW4 */{ KEY_None,   KEY_None,     KEY_None,     KEY_None,       KEY_Home,     KEY_End,      KEY_None, KEY_None, KEY_None, KEY_None, KEY_None,       KEY_None, KEY_None, KEY_None  },
/* ROW5 */{ KEY_None,   KEY_None,     KEY_None,     KEY_None,       KEY_None,     KEY_None,     KEY_None, KEY_None, KEY_None, KEY_None, KEY_None,       KEY_None, KEY_None, KEY_None  },
};  // 额外默认键盘布局 - 其它键盘布局需修改此处
const uint8_t SP_KeyArrary[][8] = {
        { 0x5,      0x0,      KEY_Delete,       0x0,      0x0,      0x0,      0x0,      0x0 }, //1 - Ctrl+Alt+Del
        { 0x3,      0x0,      KEY_Delete,       0x0,      0x0,      0x0,      0x0,      0x0 }, //2 - Ctrl+Shift+Del
        { 0x0,      0x0,      0x0,              0x0,      0x0,      0x0,      0x0,      0x0 }, //3
        { 0x0,      0x0,      0x0,              0x0,      0x0,      0x0,      0x0,      0x0 }, //4
        { 0x0,      0x0,      0x0,              0x0,      0x0,      0x0,      0x0,      0x0 }, //5
        { 0x9,      0x0,      KEY_LeftArrow,    0x0,      0x0,      0x0,      0x0,      0x0 }, //6 - GUI+Ctrl+Left
        { 0x9,      0x0,      KEY_RightArrow,   0x0,      0x0,      0x0,      0x0,      0x0 }, //7 - GUI+Ctrl+Right
};  // SP按键默认映射
const uint8_t Key_To_LEDNumber[ROW_SIZE][COL_SIZE] = {
/* ROW0 */{ 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13 },
/* ROW1 */{ 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27 },
/* ROW2 */{ 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41 },
/* ROW3 */{ 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55 },
/* ROW4 */{ 56, 255,57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68 },
/* ROW5 */{ 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82 },
};  // 矩阵键盘位置转LED编号
uint32_t Row_Pin_ALL = 0, Colum_Pin_ALL = 0;
uint8_t CustomKey[ROW_SIZE][COL_SIZE];  //自定义按键层
uint8_t Extra_CustomKey[ROW_SIZE][COL_SIZE];   //自定义额外按键层
uint8_t KeyMatrix[ROW_SIZE][COL_SIZE] = { 0 };  //按键矩阵-标记按下和未按下
uint8_t Extra_KeyMatrix[ROW_SIZE][COL_SIZE] = { 0 };  //额外层按键矩阵-标记按下和未按下
uint8_t SP_Key_Map[SP_KEY_NUMBER][8] = { 0 }; //复合按键
uint8_t KEYBOARD_data_index = 2;
Keyboard_Status_t g_keyboard_status;

static uint8_t (*KeyArr_Ptr)[COL_SIZE] = CustomKey;
static uint16_t KeyArr_ChangeTimes = 0;

/*******************************************************************************
 * Function Name  : DATAFLASH_Read_KeyArray
 * Description    : 从DataFlash读取按键矩阵
 * Input          : None
 * Return         : None
 *******************************************************************************/
void DATAFLASH_Read_KeyArray( void )
{
  HAL_Fs_Read_keyboard_mat("0:keyboard_mat.txt", (uint8_t*)CustomKey);
  HAL_Fs_Read_keyboard_mat("0:keyboard_ext_mat.txt", (uint8_t*)Extra_CustomKey);
}

/*******************************************************************************
 * Function Name  : DATAFLASH_Write_KeyArray
 * Description    : 将按键矩阵写入DataFlash
 * Input          : None
 * Return         : None
 *******************************************************************************/
void DATAFLASH_Write_KeyArray( void )
{
  HAL_Fs_Write_keyboard_mat("0:keyboard_mat.txt", (const uint8_t*)CustomKey);
  HAL_Fs_Write_keyboard_mat("0:keyboard_ext_mat.txt", (const uint8_t*)Extra_CustomKey);
}

/*******************************************************************************
 * Function Name  : KEYBOARD_Reset
 * Description    : 重置FLASH
 * Input          : None
 * Return         : None
 *******************************************************************************/
void KEYBOARD_Reset( void )
{
  uint16_t param[] = { 0, 1, 0, 0,
                       ALG_PARAM_MAGIC,
                       CAP_MOUSE_TOU_THRESH, CAP_MOUSE_REL_THRESH, CAP_MOUSE_MOVE_SPEED,
                       TOUCHBAR_TOU_THRESH, TOUCHBAR_REL_THRESH,
                       DOUBLE_TOUCH_CNT, LONG_TOUCH_CNT,
                       1, LED_DEFAULT_BRIGHTNESS, 2,  // RF频率默认2.405G
  };

  memcpy(CustomKey, KeyArrary, COL_SIZE*ROW_SIZE);
  memcpy(Extra_CustomKey, Extra_KeyArrary, COL_SIZE*ROW_SIZE);
  memcpy(SP_Key_Map, SP_KeyArrary, SP_KEY_NUMBER*8);
  DATAFLASH_Write_KeyArray( );
  HAL_Fs_Write_keyboard_spkey((uint8_t*)SP_Key_Map);
  HAL_Fs_Create_keyboard_cfg(sizeof(param)/sizeof(uint16_t), param);
  HAL_Fs_Create_readme();
}

/*******************************************************************************
 * Function Name  : KEYBOARD_ChangeKey
 * Description    : 键盘交换2个按键
 * Input          : dst_key - 目标键, src_key - 原始键
 * Return         : None
 *******************************************************************************/
void KEYBOARD_ChangeKey( uint8_t dst_key, uint8_t src_key )
{
  uint8_t i = COL_SIZE*ROW_SIZE;
  uint8_t* memaddr = &CustomKey[0][0];
  while (i) {
    --i;
    /* 交换src键和dst键 */
    if ( *(memaddr + i) == src_key ) *(memaddr + i) = dst_key;
    else if ( *(memaddr + i) == dst_key ) *(memaddr + i) = src_key;
  }
  DATAFLASH_Write_KeyArray( );
}

/*******************************************************************************
 * Function Name  : KEYBOARD_Custom_Function
 * Description    : 键盘定制化功能(检测Fn键触发的相关功能)
 * Input          : None
 * Return         : 如果不需要发送按键信息则返回0
 *******************************************************************************/
UINT8 KEYBOARD_Custom_Function( void )
{
  static uint16_t last_state = 0;
  static uint32_t press_time = 0;
  static uint8_t Fn_Mode = 0;
  static uint8_t Fn_cnt = 0;  // 4/2/1/1 bit for Reset/ChangeKey/SaveDevices/Reserved
  static uint8_t src_key = 0, dst_key = 0;
  uint16_t Udisk_mode = 1;

  if ( g_keyboard_status.Fn == TRUE && KeyboardDat->Key2 == KEY_None ) { // 按下Fn+1个键或者只有Fn键
    last_state = 1;
    press_time = sys_time;
    if ( KeyboardDat->Key1 == KEY_None && Fn_Mode == Fn_Mode_None ) { // 键盘布局复位
      Fn_Mode = Fn_Mode_Reset;
      Fn_cnt &= 0xF0;   // 清除其余计数器
    } else if ( Fn_Mode == Fn_Mode_ChangeKey ) {  // 设置改键 - 按Fn+src和Fn+dst
      if ( Fn_cnt == 0x04 ) src_key = KeyboardDat->Key1;
      else if ( Fn_cnt == 0x08 ) dst_key = KeyboardDat->Key1;
    } else if ( KeyboardDat->Key1 == KEY_C && Fn_Mode != Fn_Mode_ChangeKey ) { // 设置改键 - 先按Fn+C
      Fn_Mode = Fn_Mode_ChangeKey;
      Fn_cnt &= 0x0C;
    } else if ( KeyboardDat->Key1 == KEY_O && Fn_Mode != Fn_Mode_ChangeKey ) { // 配置参数模式
      Fn_Mode = Fn_Mode_Enter_Cfg;
      Fn_cnt = 0;
    } else if ( KeyboardDat->Key1 == KEY_R && Fn_Mode != Fn_Mode_SoftReset ) { // 软件复位模式
      Fn_Mode = Fn_Mode_SoftReset;
      Fn_cnt = 0;
    } else if ( KeyboardDat->Key1 == KEY_N && Fn_Mode != Fn_Mode_RForBLE ) { // 切换RF模式或BLE模式
      Fn_Mode = Fn_Mode_RForBLE;
      Fn_cnt = 0;
    } else if ( KeyboardDat->Key1 == KEY_M && Fn_Mode != Fn_Mode_RFJumptoBoot ) { // RF发送0x7A让接收器进BOOT
      Fn_Mode = Fn_Mode_RFJumptoBoot;
      Fn_cnt = 0;
    } else if ( KeyboardDat->Key1 == KEY_B && Fn_Mode != Fn_Mode_JumpBoot ) { // 跳转BOOT模式
      Fn_Mode = Fn_Mode_JumpBoot;
      Fn_cnt = 0;
    } else if ( KeyboardDat->Key1 == KEY_Subtraction && Fn_Mode != Fn_Mode_VolumeDown ) { // 音量减模式
      Fn_Mode = Fn_Mode_VolumeDown;
      HIDVolume[0] |= Volume_Decr;
      HID_VOL_Process();
      Fn_cnt = 0;
    } else if ( KeyboardDat->Key1 == KEY_Equal && Fn_Mode != Fn_Mode_VolumeUp ) { // 音量加模式
      Fn_Mode = Fn_Mode_VolumeUp;
      HIDVolume[0] |= Volume_Incr;
      HID_VOL_Process();
      Fn_cnt = 0;
    } else if ( KeyboardDat->Key1 == KEY_Delete && Fn_Mode != Fn_Mode_PaintedEgg ) { // 彩蛋模式
      Fn_Mode = Fn_Mode_PaintedEgg;
      Fn_cnt = 0;
    } else if ( KeyboardDat->Key1 == KEY_GraveAccent && Fn_Mode != Fn_Mode_DisEnableBLE ) { // 使能/失能蓝牙
      Fn_Mode = Fn_Mode_DisEnableBLE;
      Fn_cnt = 0;
    } else if ( KeyboardDat->Key1 == KEY_T && Fn_Mode != Fn_Mode_DisEnableTP ) { // 使能/失能小红点
      Fn_Mode = Fn_Mode_DisEnableTP;
      Fn_cnt = 0;
    } else if ( KeyboardDat->Key1 == KEY_U && Fn_Mode != Fn_Mode_UDiskMode ) { // 开启U盘模式
      Fn_Mode = Fn_Mode_UDiskMode;
      Fn_cnt = 0;
    } else if ( KeyboardDat->Key1 == KEY_0 && Fn_Mode != Fn_Mode_PriorityUSBorBLE ) { // 设置优先无线或USB
      Fn_Mode = Fn_Mode_PriorityUSBorBLE;
      Fn_cnt = 0;
    } else if ( KeyboardDat->Key1 == KEY_9 && Fn_Mode != Fn_Mode_BLE_ClearSNV ) { // 清除蓝牙SNV信息
      Fn_Mode = Fn_Mode_BLE_ClearSNV;
      Fn_cnt = 0;
    } else if ( KeyboardDat->Key1 == KEY_1 && Fn_Mode != Fn_Mode_SelectDevice1 ) { // 切换至设备1
      Fn_Mode = Fn_Mode_SelectDevice1;
      Fn_cnt = 0;
    } else if ( KeyboardDat->Key1 == KEY_2 && Fn_Mode != Fn_Mode_SelectDevice2 ) { // 切换至设备2
      Fn_Mode = Fn_Mode_SelectDevice2;
      Fn_cnt = 0;
    } else if ( KeyboardDat->Key1 == KEY_3 && Fn_Mode != Fn_Mode_SelectDevice3 ) { // 切换至设备3
      Fn_Mode = Fn_Mode_SelectDevice3;
      Fn_cnt = 0;
    } else if ( KeyboardDat->Key1 == KEY_4 && Fn_Mode != Fn_Mode_SelectDevice4 ) { // 切换至设备4
      Fn_Mode = Fn_Mode_SelectDevice4;
      Fn_cnt = 0;
    } else if ( KeyboardDat->Key1 == KEY_F1 && Fn_Mode != Fn_Mode_LED_Style1 ) { // 背光模式1
      Fn_Mode = Fn_Mode_LED_Style1;
      Fn_cnt = 0;
    } else if ( KeyboardDat->Key1 == KEY_F2 && Fn_Mode != Fn_Mode_LED_Style2 ) { // 背光模式2
      Fn_Mode = Fn_Mode_LED_Style2;
      Fn_cnt = 0;
    } else if ( KeyboardDat->Key1 == KEY_F3 && Fn_Mode != Fn_Mode_LED_Style3 ) { // 背光模式3
      Fn_Mode = Fn_Mode_LED_Style3;
      Fn_cnt = 0;
    } else if ( KeyboardDat->Key1 == KEY_F4 && Fn_Mode != Fn_Mode_LED_Style4 ) { // 背光模式4
      Fn_Mode = Fn_Mode_LED_Style4;
      Fn_cnt = 0;
    } else if ( KeyboardDat->Key1 == KEY_F5 && Fn_Mode != Fn_Mode_LED_Style5 ) { // 背光模式5
      Fn_Mode = Fn_Mode_LED_Style5;
      Fn_cnt = 0;
    } else if ( KeyboardDat->Key1 == KEY_F6 && Fn_Mode != Fn_Mode_LED_Style6 ) { // 背光模式6
      Fn_Mode = Fn_Mode_LED_Style6;
      Fn_cnt = 0;
    } else {
      if ( Fn_Mode == Fn_Mode_Reset ) return 0;
      if ( Fn_Mode != Fn_Mode_None && KeyboardDat->Key1 == KEY_None ) { // 先松开其他按键(后松开Fn)
        goto fn_do_operations;
      }
      Fn_Mode = Fn_Mode_None;
      Fn_cnt = 0;
    }
    return 0;
  } else if ( last_state > 0 && g_keyboard_status.Fn == FALSE ) {  // 松开Fn执行指令
    fn_do_operations:
    switch ( Fn_Mode ) {
      case Fn_Mode_Reset: // 按下5次Fn重置按键
        Fn_cnt += 0x10;
        if ( Fn_cnt == 0x50 ) {
          Fn_cnt = 0;
          Fn_Mode = Fn_Mode_None;
#if (defined HAL_WDG) && (HAL_WDG == TRUE)
          WWDG_ResetCfg(DISABLE); // 关看门狗
#endif
          KEYBOARD_Reset( );
#if (defined HAL_WDG) && (HAL_WDG == TRUE)
          WWDG_ResetCfg(ENABLE);  // 开看门狗
#endif
          OLED_UI_add_SHOWINFO_task("Reset OK!");
          OLED_UI_add_CANCELINFO_delay_task(3000);
        } else if ( Fn_cnt >= 0x30 ) {
          OLED_UI_add_SHOWINFO_task("%d/5 Reset", Fn_cnt >> 4);
          OLED_UI_add_CANCELINFO_delay_task(1500);
        } else if ( Fn_cnt == 0x20 && sys_time - press_time >= 3 * (1000 / FEEDDOG_PERIOD) ) {  // 第二下Fn长按进BOOT
          goto enter_boot_mode;
        }
        break;
      case Fn_Mode_ChangeKey:
        Fn_cnt += 0x04;
        if ( Fn_cnt == 0x0C ) {
          Fn_cnt = 0;
          Fn_Mode = Fn_Mode_None;
          OLED_UI_add_SHOWINFO_task("Change OK!");
          OLED_UI_add_CANCELINFO_delay_task(3000);
          KEYBOARD_ChangeKey( dst_key, src_key );
        }
        break;
      case Fn_Mode_Enter_Cfg:  // Fn+O参数配置
        Fn_Mode = Fn_Mode_None;
        if (g_keyboard_status.enter_cfg) {  // 退出界面配置
#ifdef HAL_OLED
#ifdef OLED_0_66
          OLED_UI_add_CLEARPAGE_task(2, 5);
#endif
#ifdef OLED_0_91
          // TODO
#endif
#endif
          g_keyboard_status.enter_cfg = 0;
        } else {  // 进入界面配置
#ifdef HAL_OLED
          OLED_UI_draw_menu(OLED_UI_MENU_REFRESH);
#endif
          g_keyboard_status.enter_cfg = 1;
        }
        break;
      case Fn_Mode_SoftReset:  // Fn+R软件复位
        Fn_Mode = Fn_Mode_None;
        SoftReset();
        break;
      case Fn_Mode_RForBLE:  // Fn+N切换RF或BLE模式后软件复位
        Fn_Mode = Fn_Mode_None;
        if (g_Ready_Status.rf == TRUE) DATAFLASH_Write_RForBLE(0);
        else DATAFLASH_Write_RForBLE(1);
        SoftReset();
        break;
      case Fn_Mode_RFJumptoBoot:  // Fn+M发送0x7A让接收器进BOOT
        Fn_Mode = Fn_Mode_None;
        if (g_Ready_Status.rf == TRUE) {
          tmos_set_event( RFTaskId, SBP_RF_JUMPBOOT_REPORT_EVT );  // RF JUMPBOOT事件
        }
        break;
      case Fn_Mode_JumpBoot:  // Fn+B跳转BOOT
        enter_boot_mode:
        Fn_Mode = Fn_Mode_None;
        APPJumpBoot();
        break;
      case Fn_Mode_VolumeDown:  // Fn+减号减小音量 - 松开停止
        Fn_Mode = Fn_Mode_None;
        HIDVolume[0] &= ~Volume_Decr;
        HID_VOL_Process();
        break;
      case Fn_Mode_VolumeUp:  // Fn+加号增加音量 - 松开停止
        Fn_Mode = Fn_Mode_None;
        HIDVolume[0] &= ~Volume_Incr;
        HID_VOL_Process();
        break;
      case Fn_Mode_PaintedEgg:  // Fn+Delete彩蛋
        Fn_Mode = Fn_Mode_None;
        if (g_Enable_Status.paintedegg == FALSE) {
          g_keyboard_status.changeBL = TRUE;
          led_style_func = WS2812_Style_Custom; // 彩蛋背光
          Snake_Init();
          OLED_UI_show_version(1);  // 显示版本信息
          g_Enable_Status.paintedegg = TRUE;
        } else {
          OLED_UI_show_version(0);  // 取消显示版本信息
          led_style_func = WS2812_Style_Off;
          g_Enable_Status.paintedegg = FALSE;
          tmos_start_task( halTaskID, HAL_KEYBOARD_EVENT, MS1_TO_SYSTEM_TIME(5) ); // 重新开启键盘线程
        }
        break;
      case Fn_Mode_DisEnableBLE:
        Fn_Mode = Fn_Mode_None; // Fn+波浪号关闭/开启蓝牙
        if ( g_Ready_Status.ble == FALSE && g_Ready_Status.rf == FALSE ) {
          g_Enable_Status.ble = !g_Enable_Status.ble;
          uint8_t ena_ble = g_Enable_Status.ble;
          bStatus_t status = GAPRole_SetParameter( GAPROLE_ADVERT_ENABLED, sizeof( uint8 ), &ena_ble );
          if ( status != SUCCESS ) OLED_UI_add_SHOWINFO_task("ERR %d", status);
          else if ( g_Enable_Status.ble == TRUE ) OLED_UI_add_SHOW_ICONINFO_task(OLED_UI_ICON_BLE_UNCONNECT_IDX, " ON");
          else OLED_UI_add_SHOW_ICONINFO_task(OLED_UI_ICON_BLE_UNCONNECT_IDX, " OFF");
          OLED_UI_add_CANCELINFO_delay_task(2000);
        }
        break;
      case Fn_Mode_DisEnableTP:
        Fn_Mode = Fn_Mode_None; // Fn+T关闭/开启小红点
        g_Enable_Status.tp = !g_Enable_Status.tp;
        if ( g_Enable_Status.tp == TRUE ) OLED_UI_add_SHOW_ICONINFO_task(OLED_UI_ICON_TP_IDX, " ON");
        else OLED_UI_add_SHOW_ICONINFO_task(OLED_UI_ICON_TP_IDX, " OFF");
        OLED_UI_add_CANCELINFO_delay_task(2000);
        break;
      case Fn_Mode_UDiskMode:
        Fn_Mode = Fn_Mode_None; // Fn+U开启U盘模式
        HAL_Fs_Write_keyboard_cfg(FS_LINE_UDISK_MODE, 1, &Udisk_mode);
        SoftReset();
        break;
      case Fn_Mode_PriorityUSBorBLE:  // Fn+0优先蓝牙/RF或USB切换
        Fn_Mode = Fn_Mode_None;
        extern BOOL priority_USB;
        if ( g_Ready_Status.usb == TRUE && (g_Ready_Status.ble == TRUE || g_Ready_Status.rf == TRUE) ) {  // 仅有多个连接才切换
          priority_USB = !priority_USB;
#ifdef OLED_0_91
          OLED_UI_ShowOK(26 + priority_USB * 30, 0, FALSE);
          OLED_UI_ShowOK(26 + !priority_USB * 30, 0, TRUE);
#endif
#ifdef OLED_0_66
          if ( priority_USB ) {
            OLED_UI_slot_active((uint8_t*)UI_Slot_Icon[OLED_UI_ICON_USB_IDX],
                                (uint8_t*)UI_Slot_Icon[OLED_UI_ICON_USB_IDX]);
          } else if ( g_Ready_Status.ble == TRUE ) {
            OLED_UI_slot_active((uint8_t*)UI_Slot_Icon[OLED_UI_ICON_BLE_UNCONNECT_IDX + DeviceAddress[5]],
                                (uint8_t*)UI_Slot_Icon[OLED_UI_ICON_BLE_UNCONNECT_IDX + DeviceAddress[5]]);
          } else {  // RF_Ready
            OLED_UI_slot_active((uint8_t*)UI_Slot_Icon[OLED_UI_ICON_RF_IDX],
                                (uint8_t*)UI_Slot_Icon[OLED_UI_ICON_RF_IDX]);
          }
          OLED_UI_add_default_task(OLED_UI_FLAG_DRAW_SLOT);
#endif
          if ( priority_USB ) OLED_UI_add_SHOW_ICONINFO_task(OLED_UI_ICON_USB_IDX, "Priority");
          else if ( g_Ready_Status.rf == FALSE ) OLED_UI_add_SHOW_ICONINFO_task(OLED_UI_ICON_BLE_UNCONNECT_IDX, "Priority");
          else OLED_UI_add_SHOW_ICONINFO_task(OLED_UI_ICON_RF_IDX, "Priority");
          OLED_UI_add_CANCELINFO_delay_task(2000);
        }
        break;
      case Fn_Mode_BLE_ClearSNV:  // Fn+9清除蓝牙SNV信息
        Fn_Mode = Fn_Mode_None;
        uint32_t SNV_size, p_addr = BLE_SNV_ADDR;
        uint16_t i;
        uint8_t e_buf[4] = { 0xFF, 0xFF, 0xFF, 0xFF };
#if (defined HAL_WDG) && (HAL_WDG == TRUE)
        WWDG_ResetCfg(DISABLE); // 关看门狗
#endif
//        SNV_size = 0x8000 - BLE_SNV_ADDR;
//        EEPROM_ERASE(BLE_SNV_ADDR, SNV_size);
        SNV_size = 0x70000 - BLE_SNV_ADDR;
        FLASH_ROM_ERASE( BLE_SNV_ADDR, SNV_size );
        SNV_size >>= 2;
        for (i = 0; i < SNV_size; i++) {
//          EEPROM_WRITE(p_addr, e_buf, 4); // 填充0xFF
          FLASH_ROM_WRITE(p_addr, e_buf, 4); // 填充0xFF
          p_addr += 4;
        }
#if (defined HAL_WDG) && (HAL_WDG == TRUE)
        WWDG_ResetCfg(ENABLE);  // 开看门狗
#endif
        OLED_UI_add_SHOWINFO_task("Erase OK");
        OLED_UI_add_CANCELINFO_delay_task(2000);
        break;
      case Fn_Mode_SelectDevice1 ... Fn_Mode_SelectDevice4: // 按Fn+1~4切换设备
        DeviceAddress[5] = Fn_Mode - Fn_Mode_SelectDevice1 + 1;
        Fn_Mode = Fn_Mode_None;
        OLED_UI_add_SHOW_ICONINFO_task(OLED_UI_ICON_BLE_UNCONNECT_IDX, "Device%d", DeviceAddress[5]);
        OLED_UI_add_CANCELINFO_delay_task(2000);
        tmos_start_task( hidEmuTaskId, CHANGE_ADDR_EVT, 500 );
        break;
      case Fn_Mode_LED_Style1:
        Fn_Mode = Fn_Mode_None;
        g_keyboard_status.changeBL = TRUE;
#ifdef OLED_0_91
        OLED_UI_add_SHOWSTRING_task(20, 1, "S0");
#endif
#ifdef OLED_0_66
        OLED_UI_add_SHOW_ICONINFO_task(OLED_UI_ICON_LED_STYLE_IDX, " OFF");
        OLED_UI_add_CANCELINFO_delay_task(2000);
#endif
        led_style_func = WS2812_Style_Custom;  // Fn+F1 - 关闭背光(背光保持不变)
        break;
      case Fn_Mode_LED_Style2:
        Fn_Mode = Fn_Mode_None;
        g_keyboard_status.changeBL = TRUE;
#ifdef OLED_0_91
        OLED_UI_add_SHOWSTRING_task(20, 1, "S1");
#endif
#ifdef OLED_0_66
        OLED_UI_add_SHOW_ICONINFO_task(OLED_UI_ICON_LED_STYLE_IDX, "Breath");
        OLED_UI_add_CANCELINFO_delay_task(2000);
#endif
        led_style_func = WS2812_Style_Breath;  // Fn+F2 - 背光使用呼吸灯模式
        break;
      case Fn_Mode_LED_Style3:
        Fn_Mode = Fn_Mode_None;
        g_keyboard_status.changeBL = TRUE;
#ifdef OLED_0_91
        OLED_UI_add_SHOWSTRING_task(20, 1, "S2");
#endif
#ifdef OLED_0_66
        OLED_UI_add_SHOW_ICONINFO_task(OLED_UI_ICON_LED_STYLE_IDX, "Waterful");
        OLED_UI_add_CANCELINFO_delay_task(2000);
#endif
        led_style_func = WS2812_Style_Waterful;  // Fn+F3 - 背光使用流水灯模式
        break;
      case Fn_Mode_LED_Style4:
        Fn_Mode = Fn_Mode_None;
        g_keyboard_status.changeBL = TRUE;
#ifdef OLED_0_91
        OLED_UI_add_SHOWSTRING_task(20, 1, "S3");
#endif
#ifdef OLED_0_66
        OLED_UI_add_SHOW_ICONINFO_task(OLED_UI_ICON_LED_STYLE_IDX, "Touch");
        OLED_UI_add_CANCELINFO_delay_task(2000);
#endif
        led_style_func = WS2812_Style_Touch;  // Fn+F4 - 背光使用触控呼吸灯模式
        break;
      case Fn_Mode_LED_Style5:
        Fn_Mode = Fn_Mode_None;
        g_keyboard_status.changeBL = TRUE;
#ifdef OLED_0_91
        OLED_UI_add_SHOWSTRING_task(20, 1, "S4");
#endif
#ifdef OLED_0_66
        OLED_UI_add_SHOW_ICONINFO_task(OLED_UI_ICON_LED_STYLE_IDX, "Rainbow");
        OLED_UI_add_CANCELINFO_delay_task(2000);
#endif
        led_style_func = WS2812_Style_Rainbow;  // Fn+F5 - 背光使用彩虹灯模式
        break;
      case Fn_Mode_LED_Style6:
        Fn_Mode = Fn_Mode_None;
        g_keyboard_status.changeBL = TRUE;
#ifdef OLED_0_91
        OLED_UI_add_SHOWSTRING_task(20, 1, "S5");
#endif
#ifdef OLED_0_66
        OLED_UI_add_SHOW_ICONINFO_task(OLED_UI_ICON_LED_STYLE_IDX, "Normal");
        OLED_UI_add_CANCELINFO_delay_task(2000);
#endif
        led_style_func = WS2812_Style_Normal;  // Fn+F6 - 背光使用固定亮度
        break;
      case Fn_Mode_GiveUp:
        Fn_cnt = 0;
        Fn_Mode = Fn_Mode_None;
        break;
      default:  // 未识别的指令
        ;
    }
    last_state = 0;
    return 0;
  }
  return 1;
}

/*******************************************************************************
 * Function Name  : KEYBOARD_Init
 * Description    : 键盘初始化函数
 * Input          : None
 * Return         : None
 *******************************************************************************/
void KEYBOARD_Init( void )
{
    uint8_t i;
    DATAFLASH_Read_KeyArray( );   // DataFlash载入按键
    HAL_Fs_Read_keyboard_spkey((uint8_t*)SP_Key_Map);   // DataFlash载入spKEY
    CustomKey[5][6] = KEY_Fn;   // 保证上电Fn键在对应位置 - 其它键盘布局需修改此处

    for (i = 0; i < ROW_SIZE; i++) {
        Row_Pin_ALL |= Row_Pin[i];
    }
#if (ROW_SCAN_MODE)
    Row_GPIO_(ResetBits)( Row_Pin_ALL );
    Row_GPIO_(ModeCfg)( Row_Pin_ALL, GPIO_ModeOut_PP_5mA );
    Row_GPIO_(SetBits)( Row_Pin[0] );
#else
    Row_GPIO_(ResetBits)( Row_Pin_ALL );
    Row_GPIO_(ModeCfg)( Row_Pin_ALL, GPIO_ModeIN_PU );
#endif

    for (i = 0; i < COL_SIZE; i++) {
        Colum_Pin_ALL |= Colum_Pin[i];
    }
#if (ROW_SCAN_MODE)
    Colum_GPIO_(ResetBits)( Colum_Pin_ALL );
    Colum_GPIO_(ModeCfg)( Colum_Pin_ALL, GPIO_ModeIN_PD );
#else
    Colum_GPIO_(SetBits)( Colum_Pin_ALL );
    Colum_GPIO_(ModeCfg)( Colum_Pin_ALL, GPIO_ModeOut_PP_20mA );
    Colum_GPIO_(ResetBits)( Colum_Pin[0] );
#endif
}

/*******************************************************************************
 * Function Name  : KEYBOARD_Detection
 * Description    : 键盘检测按键信息函数
 * Input          : None
 * Return         : None
 *******************************************************************************/
void KEYBOARD_Detection( void )
{
#if (ROW_SCAN_MODE)
    static uint8_t current_row = 0;
    uint8_t current_colum;
#else
    static uint8_t current_colum = 0;
    uint8_t current_row;
#endif
    static uint8_t press_Capslock = 0;  // 大于0表示CapsLock按下
    static uint8_t Touchbar_SP_Key = 0;  // 大于0表示触摸条被按下
    static BOOL press_NormalKey = FALSE;
    uint8_t key_idx, i, j;
    mpr121_operation_data_t oper_dat;

    MPR121_get_result(&oper_dat);
    /* 触摸条触发键盘按键相关 */
    if (oper_dat.slide_left == TRUE) {
        oper_dat.slide_left = FALSE;
        MPR121_set_result(&oper_dat);
        Touchbar_SP_Key = PRESS_HOLDING_TIMES;
        memcpy(KeyboardDat->data, SP_Key_Map[5], 8);  // KEY_SP_6
        g_Ready_Status.keyboard_key_data = TRUE;  // 产生事件
        return;
    } else if (oper_dat.slide_right == TRUE) {
        oper_dat.slide_right = FALSE;
        MPR121_set_result(&oper_dat);
        Touchbar_SP_Key = PRESS_HOLDING_TIMES;
        memcpy(KeyboardDat->data, SP_Key_Map[6], 8);  // KEY_SP_7
        g_Ready_Status.keyboard_key_data = TRUE;  // 产生事件
        return;
    } else if (Touchbar_SP_Key) {
        if (--Touchbar_SP_Key == 0) {  // 触摸条SP键的持续时间到达
            memset(KeyboardDat->data, 0, 8);
            KEYBOARD_data_index = 2;
            g_Ready_Status.keyboard_key_data = TRUE;  // 产生事件
        }
        return;
    }
    /* CapsLock功能相关 */
    if (KeyArr_ChangeTimes > 0 && KeyArr_ChangeTimes <= MAX_CHANGETIMES) {  // 进入CapsLock键盘布局改变计数等待
        if (KeyArr_ChangeTimes == MAX_CHANGETIMES) { // 计数值到达MAX_CHANGETIMES改变键盘布局
            KeyArr_Ptr = Extra_CustomKey;
#ifdef OLED_0_91
            OLED_UI_add_SHOWSTRING_task(2, 1, "L2");
#endif
        }
        ++KeyArr_ChangeTimes; // 键盘计数值递增
    } else if (press_Capslock) {  // CapsLock被按下
        if (--press_Capslock == 0) {  // CapsLock按下持续时间到达
          for (key_idx = 2; key_idx < 8; key_idx++) {
              if (KeyboardDat->data[key_idx] == KEY_CapsLock) {
                  memcpy(&KeyboardDat->data[key_idx], &KeyboardDat->data[key_idx] + 1, 7 - key_idx);
                  KeyboardDat->Key6 = 0;
              }
          }
          KEYBOARD_data_index--;
          g_Ready_Status.keyboard_key_data = TRUE;  // 产生事件
          return;
        }
    }
    /* 基础功能 */
#if (ROW_SCAN_MODE)
    for (current_colum = 0; current_colum < COL_SIZE; current_colum++) {    // 查询哪一列改变
        if (KeyMatrix[current_row][current_colum] == 0 && Colum_GPIO_(ReadPortPin)( Colum_Pin[current_colum] ) != 0) {  // 按下
#else
    for (current_row = 0; current_row < ROW_SIZE; current_row++) {    // 查询哪一行改变
        if (KeyMatrix[current_row][current_colum] == 0 && Row_GPIO_(ReadPortPin)( Row_Pin[current_row] ) == 0) {  // 按下
#endif
            if (g_keyboard_status.SP_Key != 0) continue;  // SP键生效后不接受其余按键
            else if (KEYBOARD_data_index >= 8 && KeyArr_Ptr[current_row][current_colum] < KEY_LeftCTRL) continue;    // 超过6个普通按键上限
            KeyMatrix[current_row][current_colum] = 1;  // 矩阵状态变成按下
            if (led_style_func == WS2812_Style_Touch && Key_To_LEDNumber[current_row][current_colum] != 0xFF) { // 触控呼吸灯模式
                LED_BYTE_Buffer[Key_To_LEDNumber[current_row][current_colum]][0] =
                LED_BYTE_Buffer[Key_To_LEDNumber[current_row][current_colum]][1] =
                LED_BYTE_Buffer[Key_To_LEDNumber[current_row][current_colum]][2] = g_LED_brightness;
            }
            g_Ready_Status.keyboard_key_data = TRUE; // 产生事件
            if (KeyArr_Ptr[current_row][current_colum] == KEY_Fn) {  // 功能键
                g_keyboard_status.Fn = TRUE;
            } else if (KeyArr_Ptr[current_row][current_colum] >= KEY_SP_1) {  // SP键(单键复合)
                g_keyboard_status.SP_Key = KeyArr_Ptr[current_row][current_colum] - KEY_SP_1;
                memcpy(KeyboardDat->data, SP_Key_Map[g_keyboard_status.SP_Key], 8);
            } else if (KeyArr_Ptr[current_row][current_colum] >= KEY_MouseL) {    // 鼠标操作
                MouseDat->data[0] |= 1 << KeyArr_Ptr[current_row][current_colum] - KEY_MouseL;
                g_Ready_Status.keyboard_mouse_data = TRUE;  // 产生鼠标事件
            } else if (KeyArr_Ptr[current_row][current_colum] >= KEY_LeftCTRL) {    // Ctrl等特殊键
                KeyboardDat->data[0] |= 1 << (KeyArr_Ptr[current_row][current_colum] - KEY_LeftCTRL);
            } else {
                if (CustomKey[current_row][current_colum] == KEY_CapsLock) {  // 长按大小写键进入Extra_CustomKey层
                    KeyArr_ChangeTimes = 1; // 键盘布局转换-开始计数
                } else {
                    KeyboardDat->data[KEYBOARD_data_index++] = KeyArr_Ptr[current_row][current_colum];
                    press_NormalKey = KeyArr_ChangeTimes > MAX_CHANGETIMES;
                }
            }
#if (ROW_SCAN_MODE)
        } else if (KeyMatrix[current_row][current_colum] != 0 && Colum_GPIO_(ReadPortPin)( Colum_Pin[current_colum] ) == 0) {   // 弹起
#else
        } else if (KeyMatrix[current_row][current_colum] != 0 && Row_GPIO_(ReadPortPin)( Row_Pin[current_row] ) != 0) {   // 弹起
#endif
            KeyMatrix[current_row][current_colum] = 0;
            g_Ready_Status.keyboard_key_data = TRUE; // 产生事件
            if (KeyArr_Ptr[current_row][current_colum] == KEY_Fn) {  // 功能键
                g_keyboard_status.Fn = FALSE;
            } else if (KeyArr_Ptr[current_row][current_colum] >= KEY_SP_1) {  // SP键(单键复合)
                g_keyboard_status.SP_Key = 0;
                memset(KeyboardDat->data, 8, 0);
            }  else if (KeyArr_Ptr[current_row][current_colum] >= KEY_MouseL) {    // 鼠标操作
                MouseDat->data[0] &= ~(1 << KeyArr_Ptr[current_row][current_colum] - KEY_MouseL);
                g_Ready_Status.keyboard_mouse_data = TRUE;  // 产生鼠标事件
            } else if (KeyArr_Ptr[current_row][current_colum] >= KEY_LeftCTRL) {    // Ctrl等特殊键
                KeyboardDat->data[0] &= ~(1 << (KeyArr_Ptr[current_row][current_colum] - KEY_LeftCTRL));
            } else {
                if (CustomKey[current_row][current_colum] == KEY_CapsLock) {  // 弹起大小写键离开Extra_CustomKey层
                    if (KeyArr_ChangeTimes > MAX_CHANGETIMES) {
                        KeyArr_Ptr = CustomKey;
#ifdef OLED_0_91
                        OLED_UI_add_SHOWSTRING_task(2, 1, "L1");
#endif
                    }
                    if (press_NormalKey == FALSE || KeyArr_ChangeTimes <= MAX_CHANGETIMES) {
                        if (KEYBOARD_data_index < 8) {
                            press_Capslock = PRESS_HOLDING_TIMES;
                            KeyboardDat->data[KEYBOARD_data_index++] = KEY_CapsLock;
                        }
                    }
                    KeyArr_ChangeTimes = 0;
                    press_NormalKey = FALSE;
                } else {
                    for (key_idx = 2; key_idx < 8; key_idx++) {
                        if (KeyboardDat->data[key_idx] == CustomKey[current_row][current_colum] ||
                            KeyboardDat->data[key_idx] == Extra_CustomKey[current_row][current_colum]) {  // 弹起按键2层都清除
                            memcpy(&KeyboardDat->data[key_idx], &KeyboardDat->data[key_idx] + 1, 7 - key_idx);
                            KeyboardDat->Key6 = 0;
                        }
                    }
                    KEYBOARD_data_index--;
                }
            }
        }
    }
#if (ROW_SCAN_MODE)
    Row_GPIO_(ResetBits)( Row_Pin[current_row++] );
    if (current_row >= ROW_SIZE) {
        current_row = 0;
    }
    Row_GPIO_(SetBits)( Row_Pin[current_row] );
#else
    Colum_GPIO_(SetBits)( Colum_Pin[current_colum++] );
    if (current_colum >= COL_SIZE) {
        current_colum = 0;
    }
    Colum_GPIO_(ResetBits)( Colum_Pin[current_colum] );
#endif
}

/*******************************************************************************
 * Function Name  : KEYBOARD_EnterNumber
 * Description    : 键盘输入数字框
 * Input          : *key - 指向输入数字的指针
 *                  *preStr - 输入前的提示
 *                  *postStr - 输入完成的提示
 *                  limit_len - 限制长度(为0不限制, 最长24)
 * Return         : 返回0表示输入完成，返回0xFF表示清空输入
 *******************************************************************************/
uint8_t KEYBOARD_EnterNumber(uint32_t *key, const char* preStr, const char* postStr, uint8_t limit_len)
{
  static uint8_t idx = 0;
  static uint32_t passkey = 0;
  static char passkey_str[25] = { '\0' };
  const uint8_t keyhash[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
  if ( KeyboardDat->Key1 == KEY_BACKSPACE ) { // 退格单独处理
      if ( idx > 0 ) {
          passkey_str[--idx] = '\0';
          passkey /= 10;
      }
      if ( passkey_str[0] == '\0' ) {
        OLED_PRINT("%s", preStr);
      } else {
        OLED_PRINT("%s", passkey_str);
      }
  } else if ( KeyboardDat->Key1 == KEY_ENTER && (idx == limit_len || limit_len == 0) ) {  // 最后一个按键是Enter则结束
      OLED_PRINT("%s", postStr);
      *key = passkey;
      passkey = idx = passkey_str[0] = 0;
      return 0;
  } else if ( KeyboardDat->Key1 >= KEY_1 && KeyboardDat->Key1 <= KEY_0 ){
      passkey = passkey * 10 + keyhash[KeyboardDat->Key1 - KEY_1];
      passkey_str[idx++] = keyhash[KeyboardDat->Key1 - KEY_1] + 0x30;
      passkey_str[idx] = '\0';
      OLED_PRINT("%s", passkey_str);
  } else if ( KeyboardDat->Key1 == KEY_ESCAPE ){  // Esc清空输入项
      passkey = idx = passkey_str[0] = 0;
      OLED_PRINT("%s", preStr);
      return 0xFF;
  }
  return 1;
}