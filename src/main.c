#include <tice.h>
#include <graphx.h>
#include <fontlibc.h>
#include <keypadc.h>

#define TIMER_FREQ      32768 /* Frequency of timer in Hz */

void PrintCentered(const char *string);
void SpriteCentered(const uint8_t num);

unsigned char palette[4] = {
    0xff, 0xff,
    0x00, 0x00
};

int main(void)
{
    uint8_t count = 1;
    timer_Disable(1);
    timer_Set(1, 0);
    timer_SetReload(1, TIMER_FREQ);
    const char *text_title = "THE KEY PRESS GAME";

    /* Initialize graphics drawing */
    gfx_Begin();
    /* gfx_SetPalette(palette, 2, 0); */
    gfx_SetPalette(palette, 4, 0);

    /* Set a font to use.  DrawString will display garbage if you don't give it a font! */
    /* fontlib_SetFont(test_font, 0); */

    /* First, we'll display centered text in a window */
    /* Add some vertical padding around our text */
    fontlib_SetLineSpacing(2, 2);
    fontlib_SetWindow(25, 40, 150, 40);
    fontlib_SetCursorPosition(25, 42);
    /* Set some random (and ugly) colors */
    fontlib_SetColors(0xC0, 0x20);
    /* This is a crazy combination of settings that you probably don't want to use in any real program, but we're using
    it here for testing purposes. */
    fontlib_SetTransparency(true);

    /* Now erase everything in the text window so you don't see that dumb filler text! */
    gfx_FillScreen(0);
    /* . . . and move cursor back to top of text window */
    /* Note that since PrintCentered takes care of setting X for us, we can just set it to 0 here */
    fontlib_SetCursorPosition(0, fontlib_GetWindowYMin());
    /* Disable pre-/post- line clearing */
    fontlib_SetNewlineOptions(FONTLIB_ENABLE_AUTO_WRAP);
    /* Show transparency in action */

    /* Now print some text in the exact center of the screen */
    fontlib_SetWindowFullScreen();
    fontlib_SetLineSpacing(0, 0);
    fontlib_SetCursorPosition(0, fontlib_GetWindowHeight() / 2 - fontlib_GetCurrentFontHeight() / 2);
    gfx_SetFontHeight(9);
    /* gfx_PrintString(text_title); */
    /* PrintCentered(text_title); */
    gfx_SetTextXY(1, 1);
    gfx_SetTextFGColor(1);
    gfx_SetTextBGColor(0);
    gfx_SetTextScale(2, 2);
    uint8_t str_long = gfx_GetStringWidth(text_title);
    gfx_PrintStringXY(text_title, 25 - str_long, 240 / 3);
    gfx_SetTextScale(1, 1);
    gfx_PrintStringXY("Press PRGM as many times as possible in 10s !",0 , 240 - 16);
    gfx_PrintStringXY("By Nicklor - ANNUL: Exit, ENTER = continue", 0, 240 - 8);
    delay(500);

    do
    {
        boot_WaitShort();
        kb_Scan();
    } while (kb_Data[6] != kb_Clear && kb_Data[6] != kb_Enter);
    if (kb_Data[6] == kb_Enter) {
        gfx_FillScreen(0);
        gfx_SetTextXY(320 / 2 - 16, 240 / 2 - 16);
        gfx_SetTextScale(2, 2);
        gfx_PrintUInt(10, 2);
        timer_Enable(1, TIMER_32K, TIMER_0INT, TIMER_DOWN);
        uint8_t prgm_press = 0;
        bool ispressed;
    
        /* Waits for a key */
        do
        {
            /* Scan the keypad to update kb_Data */
            kb_Scan();
            if (kb_IsDown(kb_KeyPrgm)) {
                ispressed = true;
            } else {
                if (ispressed == true) {
                    ispressed = false;
                    prgm_press++;
                }
            }
            
            /* If the timer is reloaded, we reached 0 */
            if (timer_ChkInterrupt(1, TIMER_RELOADED))
            {
                /* Increment number of counts */
                count++;
                gfx_FillScreen(0);
                gfx_SetTextXY(320 / 2 - 16, 240 / 2 - 16);
                gfx_PrintUInt(12 - count, 1);
    
                /* DrawBackground(count); */
    
                /* Acknowledge the reload */
                timer_AckInterrupt(1, TIMER_RELOADED);
            }
            /* Render the sprite */
    
                /* Copy the buffer to the screen */
                /* Same as gfx_Blit(gfx_buffer) */
    
        } while (kb_Data[6] != kb_Clear && count != 12);
        if (count == 12) {
            gfx_FillScreen(0);
            gfx_SetTextXY(320 / 2 - 104, 240 / 2 - 16);
            gfx_PrintString("Your score : ");
            gfx_PrintUInt(prgm_press, 1);
            do
            {
                boot_WaitShort();
                kb_Scan();
            } while (kb_Data[6] != kb_Clear && kb_Data[6] != kb_Enter);
            if (kb_Data[6] == kb_Enter) {
                main();
            }
        }
    
    }


    /* End graphics drawing */
    gfx_End();

    return 0;
}

void PrintCentered(const char *string)
{
    /* We're just using some simple math to find the center of the text window.
    Then we find the center of the text to be displayed and use math to make
    sure it ends up in the center of the window. */
    /* fontlib_SetCursorPosition(fontlib_GetWindowWidth() / 2 + fontlib_GetWindowXMin() - (fontlib_GetStringWidth(string) / 2), fontlib_GetCursorY());
    fontlib_DrawString(string); */
    gfx_SetTextXY(320 / 2, 240 / 2);
    gfx_PrintString(string);
}

/*void SpriteCentered(const uint8_t num) { */
/*     if (num == 1) { */
/*         gfx_Sprite(title, 320 - title_width, 240 - title_height); */
/*     } */
/*} */
