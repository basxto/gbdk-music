DEV?=./dev
BIN=$(DEV)/gbdk-n/bin

LCC?=lcc -Wa-l -Wl-m -Wl-j
CC=$(LCC) -c $(CFLAGS)
MKROM?=$(LCC) -Wl-yp0x0143=0x80 -Wl'-yn="GBDKMUSIC"'
EMU?=sameboy
pngconvert=$(DEV)/png2gb/png2gb.py -ci

music.gb: mainmusic.rel music.rel
	$(MKROM) $^ -o $@

playmusic:music.gb
	$(EMU) $^

%_data.c: %.png
	$(pngconvert) -u yes $^

mainmusic.rel: mainmusic.c pix/win_gbc_data.c pix/win_gbc_inv_data.c
	$(CC) -o $@ $<

%.rel: %.c
	$(CC) -o $@ $^

%.s: %.c
	$(CC) -Wf--fverbose-asm -S -o $@ $^

clean:
	rm -f *.gb *.o *.map *.lst *.sym *.rel *.ihx *.lk *.noi *.asm *.s pix/*_gb.png
	find . -maxdepth 2 -type f -regex '.*_\(map\|data\|tmap\)\.c' -delete
