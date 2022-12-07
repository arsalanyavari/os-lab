Use the command below to install Dependecies:
apt install -y build-essential flex bc libelf-dev dwarves bison qemu-kvm libncurses-dev

After compiling the kerenl and building initramfs, use the command below to run qemu virtual machine:
qemu-system-x86_64 -kernel linux-5.15.77/arch/x86/boot/bzImage -initrd initramfs.img