// ioports reads and writes bytes to ioports, using the offset.
// TODO: use the type system to guide whether to use outw, outl, etc.
use model::*;

// enough already.

/// Write 8 bits to port
unsafe fn outb(port: u16, val: u8) {
    llvm_asm!("outb %al, %dx" :: "{dx}"(port), "{al}"(val));
}

// /// Read 8 bits from port
// unsafe fn inb(port: u16) -> u8 {
//     let ret: u8;
//     llvm_asm!("inb %dx, %al" : "={ax}"(ret) : "{dx}"(port) :: "volatile");
//     return ret;
// }

// /// Write 16 bits to port
// unsafe fn outw(port: u16, val: u16) {
//     llvm_asm!("outw %ax, %dx" :: "{dx}"(port), "{al}"(val));
// }

// /// Read 16 bits from port
// unsafe fn inw(port: u16) -> u16 {
//     let ret: u16;
//     llvm_asm!("inw %dx, %ax" : "={ax}"(ret) : "{dx}"(port) :: "volatile");
//     return ret;
// }

// /// Write 32 bits to port
// unsafe fn outl(port: u16, val: u32) {
//     llvm_asm!("outl %eax, %dx" :: "{dx}"(port), "{al}"(val));
// }

// /// Read 32 bits from port
// unsafe fn inl(port: u16) -> u32 {
//     let ret: u32;
//     llvm_asm!("inl %dx, %eax" : "={ax}"(ret) : "{dx}"(port) :: "volatile");
//     return ret;
// }
pub struct IOPort;

impl Driver for IOPort {
    fn init(&mut self) -> Result<()> {
        Ok(())
    }

    fn pread(&self, _data: &mut [u8], _offset: usize) -> Result<usize> {
        Ok(0)
    }

    fn pwrite(&mut self, data: &[u8], offset: usize) -> Result<usize> {
        for (_i, &c) in data.iter().enumerate() {
            unsafe {outb(offset as u16, c);}
        }
        Ok(data.len())
    }

    fn shutdown(&mut self) {}
}
