/*------------------------------------------------*/
/* TJpgDec Quick Evaluation Program for PCs       */
/*------------------------------------------------*/

#include <rtthread.h>
#include <stdio.h>
#include <string.h>
#include "tjpgd.h"
#include <vt100.h>

/* User defined device identifier */
typedef struct {
    FILE *fp;          /* File pointer for input function */
    uint8_t *fbuf;     /* Pointer to the frame buffer for output function */
    uint16_t wfbuf;    /* Width of the frame buffer [pix] */
} IODEV;


/*------------------------------*/
/* User defined input funciton  */
/*------------------------------*/

uint16_t vt_in_func (JDEC* jd, uint8_t* buff, uint16_t nbyte)
{
    IODEV *dev = (IODEV*)jd->device;   /* Device identifier for the session (5th argument of jd_prepare function) */


    if (buff) {
        /* Read bytes from input stream */
        return (uint16_t)fread(buff, 1, nbyte, dev->fp);
    } else {
        /* Remove bytes from input stream */
        return fseek(dev->fp, nbyte, SEEK_CUR) ? 0 : nbyte;
    }
}


/*------------------------------*/
/* User defined output funciton */
/*------------------------------*/

uint16_t vt_out_func (JDEC* jd, void* bitmap, JRECT* rect)
{
    IODEV *dev = (IODEV*)jd->device;
    uint8_t *src, *dst;
    uint16_t y, bws, bwd;


    /* Put progress indicator */
    if (rect->left == 0) {
        rt_kprintf("\r%lu%%\n", (rect->top << jd->scale) * 100UL / jd->height);
    }

    /* Copy the decompressed RGB rectanglar to the frame buffer (assuming RGB888 cfg) */
    src = (uint8_t*)bitmap;
    dst = dev->fbuf + 3 * (rect->top * dev->wfbuf + rect->left);  /* Left-top of destination rectangular */
    bws = 3 * (rect->right - rect->left + 1);     /* Width of source rectangular [byte] */
    bwd = 3 * dev->wfbuf;                         /* Width of frame buffer [byte] */
    for (y = rect->top; y <= rect->bottom; y++) {
        memcpy(dst, src, bws);   /* Copy a line */
        src += bws; dst += bwd;  /* Next line */
    }

    return 1;    /* Continue to decompress */
}


/*------------------------------*/
/* Program Jpeg_Dec             */
/*------------------------------*/

int lsimg (int argc, char* argv[])
{
    void *work;       /* Pointer to the decompressor work area */
    JDEC jdec;        /* Decompression object */
    JRESULT res;      /* Result code of TJpgDec API */
    IODEV devid;      /* User defined device identifier */

    /* Open a JPEG file */
    if (argc < 2) return -1;
    devid.fp = fopen(argv[1], "rb");
    if (!devid.fp) return -1;

    /* Allocate a work area for TJpgDec */
    work = rt_malloc(3100);

    /* Prepare to decompress */
    res = jd_prepare(&jdec, vt_in_func, work, 3100, &devid);
    if (res == JDR_OK) {
        /* Ready to dcompress. Image info is available here. */
        rt_kprintf("Image dimensions: %u by %u. %u bytes used.\n", jdec.width, jdec.height, 3100 - jdec.sz_pool);

        devid.fbuf = rt_malloc(3 * jdec.width * jdec.height); /* Frame buffer for output image (assuming RGB888 cfg) */
        devid.wfbuf = jdec.width;

        res = jd_decomp(&jdec, vt_out_func, 0);   /* Start to decompress with 1/1 scaling */
        if (res == JDR_OK) {
            /* Decompression succeeded. You have the decompressed image in the frame buffer here. */
        } else {
            rt_kprintf("Failed to decompress: rc=%d\n", res);
        }
        vt_draw_rgb888_whc(devid.fbuf, jdec.height, jdec.width);
        rt_free(devid.fbuf);    /* Discard frame buffer */

    } else {
        rt_kprintf("Failed to prepare: rc=%d\n", res);
    }

    rt_free(work);             /* Discard work area */

    fclose(devid.fp);       /* Close the JPEG file */

    return res;
}
MSH_CMD_EXPORT(lsimg, ls images in msh);
