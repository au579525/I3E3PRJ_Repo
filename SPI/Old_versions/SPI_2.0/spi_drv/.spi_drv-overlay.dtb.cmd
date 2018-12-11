cmd_/home/stud/I3E3PRJ_Repo/SPI/SPI_new/spi_drv/spi_drv-overlay.dtb := mkdir -p /home/stud/I3E3PRJ_Repo/SPI/SPI_new/spi_drv/ ; arm-poky-linux-gnueabi-gcc -E -Wp,-MD,/home/stud/I3E3PRJ_Repo/SPI/SPI_new/spi_drv/.spi_drv-overlay.dtb.d.pre.tmp -nostdinc -I./scripts/dtc/include-prefixes -undef -D__DTS__ -x assembler-with-cpp -o /home/stud/I3E3PRJ_Repo/SPI/SPI_new/spi_drv/.spi_drv-overlay.dtb.dts.tmp /home/stud/I3E3PRJ_Repo/SPI/SPI_new/spi_drv/spi_drv-overlay.dts ; ./scripts/dtc/dtc -O dtb -o /home/stud/I3E3PRJ_Repo/SPI/SPI_new/spi_drv/spi_drv-overlay.dtb -b 0 -i/home/stud/I3E3PRJ_Repo/SPI/SPI_new/spi_drv/ -i./scripts/dtc/include-prefixes -Wno-unit_address_vs_reg -Wno-simple_bus_reg -Wno-unit_address_format -Wno-pci_bridge -Wno-pci_device_bus_num -Wno-pci_device_reg  -d /home/stud/I3E3PRJ_Repo/SPI/SPI_new/spi_drv/.spi_drv-overlay.dtb.d.dtc.tmp /home/stud/I3E3PRJ_Repo/SPI/SPI_new/spi_drv/.spi_drv-overlay.dtb.dts.tmp ; cat /home/stud/I3E3PRJ_Repo/SPI/SPI_new/spi_drv/.spi_drv-overlay.dtb.d.pre.tmp /home/stud/I3E3PRJ_Repo/SPI/SPI_new/spi_drv/.spi_drv-overlay.dtb.d.dtc.tmp > /home/stud/I3E3PRJ_Repo/SPI/SPI_new/spi_drv/.spi_drv-overlay.dtb.d

source_/home/stud/I3E3PRJ_Repo/SPI/SPI_new/spi_drv/spi_drv-overlay.dtb := /home/stud/I3E3PRJ_Repo/SPI/SPI_new/spi_drv/spi_drv-overlay.dts

deps_/home/stud/I3E3PRJ_Repo/SPI/SPI_new/spi_drv/spi_drv-overlay.dtb := \

/home/stud/I3E3PRJ_Repo/SPI/SPI_new/spi_drv/spi_drv-overlay.dtb: $(deps_/home/stud/I3E3PRJ_Repo/SPI/SPI_new/spi_drv/spi_drv-overlay.dtb)

$(deps_/home/stud/I3E3PRJ_Repo/SPI/SPI_new/spi_drv/spi_drv-overlay.dtb):
