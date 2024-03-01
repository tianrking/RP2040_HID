#include "../ui.h"

#include "hardware/structs/xip_ctrl.h"
// LVGL圖片聲明，假設圖片數據為C陣列的形式
// LV_IMG_DECLARE(cooneo_240x240_map);

LV_IMG_DECLARE(logo);

// // 此函數用於更新圖片的不透明度
// static void opa_anim(void * img, int32_t v)
// {
//     lv_obj_set_style_opa(img, v, LV_PART_MAIN | LV_STATE_DEFAULT);
// }

// void lv_ex_img_1(void)
// {
//     // 創建一個圖片物件，只接受一個參數：父對象
//     lv_obj_t * img = lv_img_create(lv_scr_act());

//     // 設置圖片物件的源為cooneo_240x240
//     lv_img_set_src(img, &logo);

//     // 將圖片對齊到屏幕中間
//     lv_obj_align(img,  LV_ALIGN_CENTER, 0, 0);

//     // 創建一個動畫
//     lv_anim_t a;
//     lv_anim_init(&a);
//     lv_anim_set_var(&a, img);                  // 要動畫化的圖片
//     lv_anim_set_exec_cb(&a, opa_anim);         // 指向更新不透明度的函數
//     lv_anim_set_values(&a, LV_OPA_TRANSP, LV_OPA_COVER); // 不透明度從透明變為不透明
//     lv_anim_set_time(&a, 200);                // 動畫時間為1000毫秒
//     lv_anim_set_playback_time(&a, 500);       // 回放時間也為1000毫秒
//     lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE); // 無限次重復動畫

//     // 開始動畫
//     lv_anim_start(&a);
// }


// LVGL 图片声明
LV_IMG_DECLARE(logo);

// 图片水平移动动画
static void horiz_move_anim(void * img, int32_t v)
{
    lv_obj_set_x(img, v); // 设置图片的 x 坐标
}

void lv_ex_img_1(void)
{
    // 创建一个图片对象，只接受一个参数：父对象
    lv_obj_t * img = lv_img_create(lv_scr_act());

    // 设置图片对象的源为 logo
    lv_img_set_src(img, &logo);

    // 将图片对齐到屏幕中间
    lv_obj_align(img,  LV_ALIGN_CENTER, 0, 0);

    // 创建一个动画
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, img);                  // 要动画化的图片
    lv_anim_set_exec_cb(&a, horiz_move_anim);  // 指向更新水平位置的函数
    lv_anim_set_values(&a, -50, 300);          // 水平位置从 -50 变化到 300
    lv_anim_set_time(&a, 2000);                // 动画时间为 2000 毫秒
    lv_anim_set_playback_time(&a, 1000);       // 回放时间也为 1000 毫秒
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE); // 无限次重复动画

    // 开始动画
    lv_anim_start(&a);
}