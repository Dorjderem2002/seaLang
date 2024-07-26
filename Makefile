ASM=nasm

src_dir=src
build_dir=build

.PHONY: all floppy_image kernel bootloader clean always

#FLOPPY IMAGE
floppy_image: $(build_dir)/main_floppy.img

$(build_dir)/main_floppy.img: bootloader kernel
	dd if=/dev/zero of=$(build_dir)/main_floppy.img bs=512 count=2880
	mkfs.fat -F 12 -n "NBOS" $(build_dir)/main_floppy.img
	dd if=$(build_dir)/bootloader.bin of=$(build_dir)/main_floppy.img conv=notrunc
	mcopy -i $(build_dir)/main_floppy.img $(build_dir)/kernel.bin "::kernel.bin"

# BOOTLOADER
bootloader: $(build_dir)/bootloader.bin
$(build_dir)/bootloader.bin: always
	$(ASM) $(src_dir)/bootloader/boot.asm -f bin -o $(build_dir)/bootloader.bin

# KERNEL
kernel: $(build_dir)/kernel.bin

$(build_dir)/kernel.bin: always
	$(ASM) $(src_dir)/kernel/main.asm -f bin -o $(build_dir)/kernel.bin

# always
always:
	mkdir -p $(build_dir)

#clean
clean:
	rm -rf $(build_dir)/*