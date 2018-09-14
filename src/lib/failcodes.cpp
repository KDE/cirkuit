#include "failcodes.h"

const char* GetErrorString(int f)
{
   switch (f) {
        case NoFail : return "No failure";
        case Fail_LateXExec : return "Error: latex failed to execute. Check log for syntax errors";
        case Fail_PdfLateXExec : return "Error: pdflatex failed to execute. Check log for syntax errors";
        case Fail_LateXNoOutput : return "Error: latex produced no output. Check log for syntax errors";
        case Fail_PdfLateXNoOutput : return "Pdflatex produced no output. Check log for syntax errors";
        case Fail_m4 : return "Error: m4 failed to execute. Is it installed?";
        case Fail_dpic : return "Error: dpic failed to execute. Check log for syntax errors";
        case Fail_gpic : return "Error: gpic -t failed to execute. Check log for syntax errors";
        case Fail_pic : return "Error: gpic -t failed to execute. Check log for syntax errors";
        case Fail_dvips : return "Error: dvips failed to execute. Is it installed?";
        case Fail_epstool : return "Error: epstool failed to execute. Nothing to draw?";
        case Fail_ps2epsi : return "Error: ps2epsi failed to execute. Is it installed?";
        case Fail_ps2pdf : return "Error: ps2pdf failed to execute. Is it installed?";
        case Fail_ps2ps : return "Error: ps2ps failed to execute. Is it installed?";
        case Fail_epstopdf : return "Error: epstopdf failed to execute. Nothing to draw?";
        case Fail_pdf2svg : return "Error: pdf2svg failed to execute. Is it installed?";
        case Fail_poppler_pdftoppm : return "Error: pdftoppm failed to execute. Is Poppler-Qt5 installed?";
        case Fail_pdftops : return "Error: pdftops failed to execute. Is it installed?";
        case Fail_imagemagick_convert : return "Convert failed to execute. Is ImageMagick installed?";
        case Fail_gnuplot : return "Error: gnuplot failed to execute. Check log for syntax errors";
        case Fail_unimplemented_conversion : return "Internal error: Unimplemented conversion";
    default : return "Unrecognised error code";
    };
   return "Never returned";
};
