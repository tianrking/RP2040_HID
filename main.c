#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "bsp/board.h"
#include "tusb.h"
#include "hardware/gpio.h"
#include "usb_descriptors.h"

//--------------------------------------------------------------------+
// MACRO CONSTANT TYPEDEF PROTYPES
//--------------------------------------------------------------------+
//#define M_PI 3.1415926
/* Blink pattern
 * - 250 ms  : device not mounted
 * - 1000 ms : device mounted
 * - 2500 ms : device is suspended
 */
enum  {
  BLINK_NOT_MOUNTED = 250,
  BLINK_MOUNTED = 1000,
  BLINK_SUSPENDED = 2500,
};

// 全局声明 GPIO 引脚变量
const uint PIN_GP2 = 2;
const uint PIN_GP3 = 3;
const uint PIN_GP4 = 4;
const uint PIN_GP5 = 5;
const uint PIN_GP6 = 6;
const uint PIN_GP7 = 7;
const uint PIN_GP8 = 8;
const uint PIN_GP9 = 9;

bool gp2_state; //= gpio_get(PIN_GP2) == 0;  // 当 GP2 接地时为真
bool gp3_state; //= gpio_get(PIN_GP3) == 0;  // 当 GP3 接地时为真
bool gp4_state; //= gpio_get(PIN_GP4) == 0;  // 当 GP4 接地时为真
bool gp5_state; //= gpio_get(PIN_GP5) == 0;  // 当 GP5 接地时为真

static uint32_t blink_interval_ms = BLINK_NOT_MOUNTED;
void hid_mouse_circle_task(int direct);
void led_blinking_task(void);
void hid_task(void);
void hid_mouse_circle_task(int direct);
void send_wifi_connect_sequence(void);

void setup_gpio(void);
/*------------- MAIN -------------*/
int main(void)
{
  board_init();
  tusb_init();
  setup_gpio();
  while (1)
  {
    tud_task(); // tinyusb device task
    led_blinking_task();

    hid_task();
  }
}

//--------------------------------------------------------------------+
// Device callbacks
//--------------------------------------------------------------------+

// wifi connect
//
void send_key(uint8_t key) {
    uint8_t keycode[6] = {0};
    keycode[0] = key;
    tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode);
    sleep_ms(10);
    tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL); // 发送空报告以模拟键盘释放
    sleep_ms(10);
}

void open_terminal() {
    // 模拟 Ctrl+Alt+T 发送终端命令
    tud_hid_keyboard_report(REPORT_ID_KEYBOARD, KEYBOARD_MODIFIER_LEFTCTRL | KEYBOARD_MODIFIER_LEFTALT, (uint8_t[]){HID_KEY_T});
    sleep_ms(10);
    tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL); // 模拟键盘释放
    sleep_ms(500); // 等待终端打开
}

void input_wifi_command() {
    // 模拟输入命令 "nmcli c up WorldMaker"
    char cmd[] = "nmcli c up WorldMaker";
    for (int i = 0; cmd[i] != '\0'; i++) {
        // 这里需要将字符映射到对应的键盘扫描码
        //uint8_t key = ... // 字符到扫描码的映射
        //send_key(key);
	send_key(cmd[i]);
    }
    send_key(HID_KEY_ENTER);
}

/// startup
void send_combination(uint8_t modifier, uint8_t key) {
    uint8_t keycode[6] = {0};
    keycode[0] = key;
    tud_hid_keyboard_report(REPORT_ID_KEYBOARD, modifier, keycode);
    sleep_ms(10);
    tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL); // 模拟键盘释放
    sleep_ms(10);
}

void alt_tab() {
    send_combination(KEYBOARD_MODIFIER_LEFTALT, HID_KEY_TAB);
}

void alt_f4() {
    send_combination(KEYBOARD_MODIFIER_LEFTALT, HID_KEY_F4);
}

void refresh_f5() {
    send_combination(0, HID_KEY_F5);
}

void windows_e() {
    send_combination(KEYBOARD_MODIFIER_LEFTGUI, HID_KEY_E);
}

void windows_r() {
    send_combination(KEYBOARD_MODIFIER_LEFTGUI, HID_KEY_R);
}

///
///circle task
//
void hid_mouse_circle_task(int direct) {
    static int angle = 0; // 角度变量
    const int radius = 10; // 圆形轨迹的半径
    const int circle_speed = 5; // 移动速度（角度增量）

    // 使用正弦和余弦函数计算增量
    int8_t x_move = radius * cos(angle * M_PI / 180);
    int8_t y_move = radius * sin(angle * M_PI / 180);

    // 发送鼠标移动报告
    if(direct == 1)
    	tud_hid_mouse_report(REPORT_ID_MOUSE, 0x00, x_move, y_move, 0, 0);
    if(direct == -1)
	tud_hid_mouse_report(REPORT_ID_MOUSE, 0x00, -x_move, -y_move, 0, 0);
    // 更新角度
    angle = (angle + circle_speed) % 360;
}

//
void setup_gpio() {
    // 初始化 GPIO 为输入模式，并启用内部上拉电阻
    const uint PIN_GP2 = 2;
    const uint PIN_GP3 = 3;
    const uint PIN_GP4 = 4;
    const uint PIN_GP5 = 5;
    const uint PIN_GP6 = 6;
    const uint PIN_GP7 = 7;
    gpio_init(PIN_GP2);
    gpio_init(PIN_GP3);
    gpio_init(PIN_GP4);
    gpio_init(PIN_GP5);

    gpio_set_dir(PIN_GP2, GPIO_IN);
    gpio_set_dir(PIN_GP3, GPIO_IN);
    gpio_set_dir(PIN_GP4, GPIO_IN);
    gpio_set_dir(PIN_GP5, GPIO_IN);

    gpio_pull_up(PIN_GP2);
    gpio_pull_up(PIN_GP3);
    gpio_pull_up(PIN_GP4);
    gpio_pull_up(PIN_GP5);

    gpio_init(PIN_GP6);
    gpio_set_dir(PIN_GP6, GPIO_IN);
    gpio_pull_up(PIN_GP6);

    gpio_init(PIN_GP7);
    gpio_set_dir(PIN_GP7, GPIO_IN);
    gpio_pull_up(PIN_GP7);

    gpio_init(PIN_GP8);
    gpio_set_dir(PIN_GP8, GPIO_IN);
    gpio_pull_up(PIN_GP8);

    gpio_init(PIN_GP9);
    gpio_set_dir(PIN_GP9, GPIO_IN);
    gpio_pull_up(PIN_GP9);
}


// Invoked when device is mounted
void tud_mount_cb(void)
{
  blink_interval_ms = BLINK_MOUNTED;
}

// Invoked when device is unmounted
void tud_umount_cb(void)
{
  blink_interval_ms = BLINK_NOT_MOUNTED;
}

// Invoked when usb bus is suspended
// remote_wakeup_en : if host allow us  to perform remote wakeup
// Within 7ms, device must draw an average of current less than 2.5 mA from bus
void tud_suspend_cb(bool remote_wakeup_en)
{
  (void) remote_wakeup_en;
  blink_interval_ms = BLINK_SUSPENDED;
}

// Invoked when usb bus is resumed
void tud_resume_cb(void)
{
  blink_interval_ms = BLINK_MOUNTED;
}

//--------------------------------------------------------------------+
// USB HID
//--------------------------------------------------------------------+
void send_empty_report() {
    uint8_t empty_keys[6] = {0}; // 所有键位都未被按下
    tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, empty_keys); // 发送空键盘报告
}

    bool last_state_gp2 = true;
    bool last_state_gp3 = true;
    bool last_state_gp4 = true;
    bool last_state_gp5 = true;
    bool last_state_gp6 = true;
    bool last_state_gp7 = true;
    bool last_state_gp8 = true;
    bool last_state_gp9 = true;

static void send_hid_report(uint8_t report_id, uint32_t btn)
{
  // skip if hid is not ready yet
	
  if ( !tud_hid_ready() ) return;

	bool current_state_gp2 = gpio_get(PIN_GP2) == 0;
        bool current_state_gp3 = gpio_get(PIN_GP3) == 0;
        bool current_state_gp4 = gpio_get(PIN_GP4) == 0;
        bool current_state_gp5 = gpio_get(PIN_GP5) == 0;
        bool current_state_gp6 = gpio_get(PIN_GP6) == 0;
        bool current_state_gp7 = gpio_get(PIN_GP7) == 0;
        bool current_state_gp8 = gpio_get(PIN_GP8) == 0;
        bool current_state_gp9 = gpio_get(PIN_GP9) == 0;
    // 音量控制
    if (gp4_state) {
        // 音量减小
        uint16_t volume_decrement = HID_USAGE_CONSUMER_VOLUME_DECREMENT;
        tud_hid_report(REPORT_ID_CONSUMER_CONTROL, &volume_decrement, 2);
    } else if (gp5_state) {
        // 音量增加
        uint16_t volume_increment = HID_USAGE_CONSUMER_VOLUME_INCREMENT;
        tud_hid_report(REPORT_ID_CONSUMER_CONTROL, &volume_increment, 2);
    }


        if (!current_state_gp6 && last_state_gp6) {
            alt_tab();
	    send_empty_report();
        }

        if (!current_state_gp7 && last_state_gp7) {
            alt_f4();
	    send_empty_report();
        }

        if (!current_state_gp8 && last_state_gp8) {
            refresh_f5();
	    send_empty_report();
        }

        if (!current_state_gp9 && last_state_gp9) {
            windows_e();
	    send_empty_report();
            sleep_ms(500); // 假设按 GP9 后要打开资源管理器，需要稍长延时
        }

last_state_gp2 = current_state_gp2;
last_state_gp3 = current_state_gp3;
last_state_gp4 = current_state_gp4;
last_state_gp5 = current_state_gp5;
last_state_gp6 = current_state_gp6;
last_state_gp7 = current_state_gp7;
last_state_gp8 = current_state_gp8;
last_state_gp9 = current_state_gp9;
  switch(report_id)
  {
    case REPORT_ID_KEYBOARD:
    {
      // use to avoid send multiple consecutive zero report for keyboard
      static bool has_keyboard_key = false;

      if ( btn ||gpio_get(PIN_GP2) == 0)
      {
        uint8_t keycode[6] = { 0 };
        keycode[0] = HID_KEY_A;

        tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode);
        has_keyboard_key = true;
      }else
      {
        // send empty key report if previously has key pressed
        if (has_keyboard_key) tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
        has_keyboard_key = false;
      }
    }
    break;

    case REPORT_ID_MOUSE:
    {
      int8_t const delta = 5;

      // no button, right + down, no scroll, no pan
      if(gpio_get(PIN_GP2)==0)
      	hid_mouse_circle_task(1);
      if(gpio_get(PIN_GP3)==0)
	hid_mouse_circle_task(-1);
      //tud_hid_mouse_report(REPORT_ID_MOUSE, 0x00, delta, delta, 0, 0);
    }
    break;

    case REPORT_ID_CONSUMER_CONTROL:
    {
      // use to avoid send multiple consecutive zero report
      static bool has_consumer_key = false;

      if ( btn )
      {
        // volume down
        uint16_t volume_down = HID_USAGE_CONSUMER_VOLUME_DECREMENT;
        tud_hid_report(REPORT_ID_CONSUMER_CONTROL, &volume_down, 2);
        has_consumer_key = true;
      }else
      {
        // send empty key report (release key) if previously has key pressed
        uint16_t empty_key = 0;
        if (has_consumer_key) tud_hid_report(REPORT_ID_CONSUMER_CONTROL, &empty_key, 2);
        has_consumer_key = false;
      }
    }
    break;

    case REPORT_ID_GAMEPAD:
    {
      // use to avoid send multiple consecutive zero report for keyboard
      static bool has_gamepad_key = false;

      hid_gamepad_report_t report =
      {
        .x   = 0, .y = 0, .z = 0, .rz = 0, .rx = 0, .ry = 0,
        .hat = 0, .buttons = 0
      };

      if ( btn )
      {
        report.hat = GAMEPAD_HAT_UP;
        report.buttons = GAMEPAD_BUTTON_A;
        tud_hid_report(REPORT_ID_GAMEPAD, &report, sizeof(report));

        has_gamepad_key = true;
      }else
      {
        report.hat = GAMEPAD_HAT_CENTERED;
        report.buttons = 0;
        if (has_gamepad_key) tud_hid_report(REPORT_ID_GAMEPAD, &report, sizeof(report));
        has_gamepad_key = false;
      }
    }
    break;

    default: break;
  }
}

// Every 10ms, we will sent 1 report for each HID profile (keyboard, mouse etc ..)
// tud_hid_report_complete_cb() is used to send the next report after previous one is complete
void hid_task(void)
{
  // Poll every 10ms
  const uint32_t interval_ms = 10;
  static uint32_t start_ms = 0;

  if ( board_millis() - start_ms < interval_ms) return; // not enough time
  start_ms += interval_ms;

  uint32_t const btn = board_button_read();

  // Remote wakeup
  if ( tud_suspended() && btn )
  {
    // Wake up host if we are in suspend mode
    // and REMOTE_WAKEUP feature is enabled by host
    tud_remote_wakeup();
  }else
  {
    // Send the 1st of report chain, the rest will be sent by tud_hid_report_complete_cb()
    send_hid_report(REPORT_ID_KEYBOARD, btn);
  }
}

// Invoked when sent REPORT successfully to host
// Application can use this to send the next report
// Note: For composite reports, report[0] is report ID
void tud_hid_report_complete_cb(uint8_t instance, uint8_t const* report, uint16_t len)
{
  (void) instance;
  (void) len;

  uint8_t next_report_id = report[0] + 1;

  if (next_report_id < REPORT_ID_COUNT)
  {
    send_hid_report(next_report_id, board_button_read());
  }
}

// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen)
{
  // TODO not Implemented
  (void) instance;
  (void) report_id;
  (void) report_type;
  (void) buffer;
  (void) reqlen;

  return 0;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize)
{
  (void) instance;

  if (report_type == HID_REPORT_TYPE_OUTPUT)
  {
    // Set keyboard LED e.g Capslock, Numlock etc...
    if (report_id == REPORT_ID_KEYBOARD)
    {
      // bufsize should be (at least) 1
      if ( bufsize < 1 ) return;

      uint8_t const kbd_leds = buffer[0];

      if (kbd_leds & KEYBOARD_LED_CAPSLOCK)
      {
        // Capslock On: disable blink, turn led on
        blink_interval_ms = 0;
        board_led_write(true);
      }else
      {
        // Caplocks Off: back to normal blink
        board_led_write(false);
        blink_interval_ms = BLINK_MOUNTED;
      }
    }
  }
}

//--------------------------------------------------------------------+
// BLINKING TASK
//--------------------------------------------------------------------+
void led_blinking_task(void)
{
  static uint32_t start_ms = 0;
  static bool led_state = false;

  // blink is disabled
  if (!blink_interval_ms) return;

  // Blink every interval ms
  if ( board_millis() - start_ms < blink_interval_ms) return; // not enough time
  start_ms += blink_interval_ms;

  board_led_write(led_state);
  led_state = 1 - led_state; // toggle
}
