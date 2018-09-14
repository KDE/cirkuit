#ifndef FAILCODES_H
#define FAILCODES_H

    enum FailCode {
        NoFail = 0,
        Fail_LateXExec = 1,
        Fail_PdfLateXExec = 2,
        Fail_LateXNoOutput = 3,
        Fail_PdfLateXNoOutput = 4,
        Fail_m4 = 5,
        Fail_dpic = 6,
        Fail_gpic = 7,
        Fail_pic = 8,
        Fail_dvips = 9,
        Fail_epstool = 10,
        Fail_ps2epsi = 11,
        Fail_ps2pdf = 12,
        Fail_ps2ps = 13,
        Fail_epstopdf = 14,
        Fail_pdf2svg = 15,
        Fail_poppler_pdftoppm = 16,
        Fail_pdftops = 17,
        Fail_imagemagick_convert = 18,
        Fail_gnuplot = 19,
        Fail_unimplemented_conversion = 20
    };


const char* GetErrorString(int f);

#endif // FAILCODES_H
