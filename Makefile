DEV?=./dev
BIN=$(DEV)/gbdk-n/bin

CC=$(BIN)/gbdk-n-compile.sh
LK?=$(BIN)/gbdk-n-link.sh
MKROM?=makebin -Z -yc
EMU?=vbam --no-pause-when-inactive -f1
pngconvert=$(DEV)/png2gb/png2gb.py

music.gb: mainmusic.ihx
	$(MKROM) $^ $@

playmusic:music.gb
	$(EMU) $^

mainmusic.ihx: mainmusic.rel music.rel
	$(LK) -o $@ $^

%_data.c: %.png
	$(pngconvert) -u yes $^

mainmusic.rel: mainmusic.c pix/win_gbc_data.c pix/win_gbc_inv_data.c
	$(CC) -o $@ $<

%.rel: %.c
	$(CC) -o $@ $^

gbdk-n:
	$(MAKE) -C $(DEV)/gbdk-n

clean:
	rm -f *.gb *.o *.map *.lst *.sym *.rel *.ihx *.lk *.noi *.asm pix/*_gb.png
	find . -maxdepth 2 -type f -regex '.*_\(map\|data\|tmap\)\.c' -delete
