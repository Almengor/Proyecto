#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include "hpdf.h"

jmp_buf env;

#ifdef HPDF_DLL
void __stdcall
#demás
vacío
#terminara si
error_handler(HPDF_STATUS error_no,
    HPDF_STATUS detalle_no,
    void* user_data)
{
    printf("ERROR: error_no =% 04X, detail_no =% u \ n", (HPDF_UINT)error_no,
        (HPDF_UINT)detalle_no);
    longjmp(env, 1);
}

int main(int argc, char** argv)
{
    HPDF_Doc pdf;
    char fname[256];
    HPDF_Page page;
    HPDF_Font title_font;
    HPDF_Font detail_font;
    HPDF_UINT page_height;
    HPDF_UINT page_width;
    HPDF_REAL pw;
    char SAMP_TXT[2048];
    const char* nombre_fuente_detalle;
    ARCHIVO* f;

    si(argc < 2) {
        printf("ttfont_jp_demo <ttf-font-filename> [-E] \ n");
        printf("ttfont_jp_demo <ttc-font-filename> <index> [-E] \ n");
        return 1;
    }

#ifdef __WIN32__
    f = fopen("mbtext \\ sjis.txt", "rb");
    #demás
        f = fopen("mbtext / sjis.txt", "rb");
    #terminara si

        si(!f) {
        printf("error: no se puede abrir 'mbtext / sjis.txt' \ n");
        return 1;
    }

    fgets(SAMP_TXT, 2048, f);
    fclose(f);

    strcpy(fname, argv[0]);
    strcat(fname, ".pdf");

    pdf = HPDF_New(manejador_error, NULL);
    if (!pdf) {
        printf("error: no se puede crear un objeto PdfDoc \ n");
        return 1;
    }

    si(setjmp(env)) {
        HPDF_Free(pdf);
        return 1;
    }

    / *declaración para usar codificación japonesa. * /
        HPDF_UseJPEncodings(pdf);

    HPDF_SetCompressionMode(pdf, HPDF_COMP_ALL);

    / *cargar archivo ttc * /
        si(argc == 4 && strcmp(argv[3], "-E") == 0)
        nombre_fuente_detalle = HPDF_LoadTTFontFromFile2(pdf, argv[1],
            atoi(argv[2]), HPDF_TRUE);
    más si(argc == 3 && strcmp(argv[2], "-E") == 0)
        nombre_fuente_detalle = HPDF_LoadTTFontFromFile(pdf, argv[1], HPDF_TRUE);
    más si(argc == 3)
        nombre_fuente_detalle = HPDF_LoadTTFontFromFile2(pdf, argv[1],
            atoi(argv[2]), HPDF_FALSE);
    demás
        nombre_fuente_detalle = HPDF_LoadTTFontFromFile(pdf, argv[1], HPDF_FALSE);

    / *agregar un nuevo objeto de página. * /
        página = HPDF_AddPage(pdf);

    title_font = HPDF_GetFont(pdf, "Helvetica", NULL);

    fuente_detalle = HPDF_GetFont(pdf, nombre_fuente_detalle, "90msp-RKSJ-H");

    HPDF_Page_SetFontAndSize(página, fuente_título, 10);

    HPDF_Page_BeginText(página);

    / *mueve la posición del texto a la parte superior de la página. * /
        HPDF_Page_MoveTextPos(página, 10, 190);
    HPDF_Page_ShowText(página, nombre_fuente_detalle);
    HPDF_Page_ShowText(página, "(");
    HPDF_Page_ShowText(página, HPDF_Font_GetEncodingName(detalle_fuente));
    HPDF_Page_ShowText(página, ")");

    HPDF_Page_SetFontAndSize(página, fuente_detalle, 15);
    HPDF_Page_MoveTextPos(página, 10, -20);
    HPDF_Page_ShowText(página, "abcdefghijklmnopqrstuvwxyz");
    HPDF_Page_MoveTextPos(página, 0, -20);
    HPDF_Page_ShowText(página, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    HPDF_Page_MoveTextPos(página, 0, -20);
    HPDF_Page_ShowText(página, "1234567890");
    HPDF_Page_MoveTextPos(página, 0, -20);

    HPDF_Page_SetFontAndSize(página, fuente_detalle, 10);
    HPDF_Page_ShowText(página, SAMP_TXT);
    HPDF_Page_MoveTextPos(página, 0, -18);

    HPDF_Page_SetFontAndSize(página, fuente_detalle, 16);
    HPDF_Page_ShowText(página, SAMP_TXT);
    HPDF_Page_MoveTextPos(página, 0, -27);

    HPDF_Page_SetFontAndSize(página, fuente_detalle, 23);
    HPDF_Page_ShowText(página, SAMP_TXT);
    HPDF_Page_MoveTextPos(página, 0, -36);

    HPDF_Page_SetFontAndSize(página, fuente_detalle, 30);
    HPDF_Page_ShowText(página, SAMP_TXT);
    HPDF_Page_MoveTextPos(página, 0, -36);

    pw = HPDF_Page_TextWidth(página, SAMP_TXT);
    altura_pagina = 210;
    ancho_página = pw + 40;

    HPDF_Page_SetWidth(página, ancho de página);
    HPDF_Page_SetHeight(página, altura_página);

    / *finalizar para imprimir texto. * /
        HPDF_Page_EndText(página);

    HPDF_Page_SetLineWidth(página, 0, 5);

    HPDF_Page_MoveTo(página, 10, altura_página - 25);
    HPDF_Page_LineTo(página, ancho de página - 10, altura_de página - 25);
    HPDF_Page_Stroke(página);

    HPDF_Page_MoveTo(página, 10, altura_página - 85);
    HPDF_Page_LineTo(página, ancho de página - 10, altura_de página - 85);
    HPDF_Page_Stroke(página);

    HPDF_SaveToFile(pdf, fname);

    /* limpiar */
    HPDF_Free(pdf);

    return 0;
}


