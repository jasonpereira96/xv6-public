.code16
.globl start
start:
movb $0x0e, %ah  # interrupt code
lea hello, %di # load the starting address of the string into the data index register
movb $0,    %bh  # page number
movb $7,    %bl  # colour
movb $0x45, %cl # initialize counter with the length of the string

loop:
movb (%di), %al # move a char into al
int $0x10 # print the char in al
inc %di # increment the data index to point to the next char in the string
dec %cl # decrement the counter
jnz loop # if there are more chars remaining, repeat

movb $0x00, %ah  # interrupt code to wait for a keypress
int $0x16 # wait for a keypress

movb $0x00, %ah  # interrupt code
movb $0x13, %al  # 320x200, 256 color graphics
int $0x10 # set video mode

movw $0xa000, %ax # first 4 digits of the starting base address of video memory. This will serve as our base for segmented addressing
movw %ax, %ds # move it into ds to serve as base address
movb $0xf, %al # a white pixel
movw $0, %di # the first pixel at the top left corner of the screen
movb %al, %ds: (%di) # move the white pixel into video memory

# move the address of diskpacket into si
lea diskpacket, %ax
movw %ax, %si
# move 00h into ds
movw $0x00, %ax
movw %ax, %ds

movb $0x42, %ah # set the interrupt code
movb $0x80, %dl # set the drive number to read from. 80h is the first drive
int $0x13 # call the interrupt to read the image from disk

# wait for another keypress
movb $0x00, %ah  # interrupt code to wait for a keypress
int $0x16 # wait for a keypress

# changing background color to lavender (RGB: #9a9aeb)
movw $0x1010, %ax # interrupt code
movw $0x0f, %bx # color to change: in this case, white
movb $0x9a, %dh # red component of lavender
movb $0x9a, %ch # green component of lavender
movb $0xeb, %cl # blue component of lavender
int $0x10 # call the interrupt to change the colour palette

# wait for another keypress
movb $0x00, %ah  # interrupt code to wait for a keypress
int $0x16 # wait for a keypress

stop:
jmp stop

diskpacket:
.byte 0x10 # size of packet
.byte 0x00 # reserved - set to 0
.byte 0x7d # number of sectors to read
.byte 0x00 # unused
.word 0x0000 # offset
.word 0xa000 # segment
.quad 0x00000001 # starting absolute block number

hello:
.string "Welcome to xv6@UIC. Press any key to continue"

.org 0x1fe
.word 0xAA55