require conf/machine/include/gigablue-arm.inc

KERNELVERSION = "4.1.20"

DVBSKYPROVIDER = "kernel"

MACHINE_FEATURES += "colorlcd gigabluelcd gigabluelcd220 ci blindscan-dvbs blindscan-dvbc transcoding dvb-c mountboot bluetooth"

SOC_FAMILY = "bcm72604"

SRCDATE_BOLT = "20190926"

PREFERRED_VERSION_linux-gigablue = "${KERNELVERSION}"
PREFERRED_PROVIDER_virtual/kernel = "linux-gigablue"
PREFERRED_PROVIDER_virtual/egl = "gb-v3ddriver-gb72604"
PREFERRED_PROVIDER_virtual/libgles2 = "gb-v3ddriver-gb72604"

IMAGE_CMD_tar_prepend = "\
    mkdir -p ${IMGDEPLOYDIR}/${IMAGEDIR}; \
    cp ${DEPLOY_DIR_IMAGE}/${MACHINE}_boot.bin ${IMGDEPLOYDIR}/${IMAGEDIR}/boot.bin; \
    cp ${DEPLOY_DIR_IMAGE}/${MACHINE}_gpt.bin ${IMGDEPLOYDIR}/${IMAGEDIR}/gpt.bin; \
    cp ${DEPLOY_DIR_IMAGE}/${MACHINE}_rescue.bin ${IMGDEPLOYDIR}/${IMAGEDIR}/rescue.bin; \
    ${@bb.utils.contains("MACHINE_FEATURES", "bolt", "cp ${DEPLOY_DIR_IMAGE}/${MACHINE}_bolt_${SRCDATE_BOLT}.bin ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/bolt_${SRCDATE_BOLT}.bin;" , "", d)} \
    cp ${DEPLOY_DIR_IMAGE}/zImage ${IMGDEPLOYDIR}/${IMAGEDIR}/${KERNEL_FILE}; \
    echo ${IMAGE_NAME} > ${IMGDEPLOYDIR}/${IMAGEDIR}/imageversion; \
    cd ${IMAGE_ROOTFS}; \
    tar -cvf ${IMGDEPLOYDIR}/rootfs.tar -C ${IMAGE_ROOTFS} .; \
    mv ${IMGDEPLOYDIR}/rootfs.tar ${IMGDEPLOYDIR}/${IMAGEDIR}/rootfs.tar; \
    bzip2 ${IMGDEPLOYDIR}/${IMAGEDIR}/rootfs.tar; \
    cd ${IMGDEPLOYDIR}; \
    zip ${IMAGE_NAME}_usb.zip ${IMAGEDIR}/*; \
    rm -f ${DEPLOY_DIR_IMAGE}/*.tar.bz2; \
    rm -Rf gigablue; \
"

MACHINE_ESSENTIAL_EXTRA_RDEPENDS += "\
	gigablue-platform-util-gb72604 \
	gigablue-ddbootup \
	gigablue-swapcreate \
	gb-v3ddriver-gb72604 \
	gstreamer1.0-plugin-dvbmediasink \
	"

EXTRA_IMAGEDEPENDS += "\
	gigablue-initrd-cfe-${MACHINE} \
	"

IMAGE_INSTALL_append = " \
	bluetoothsetup-gb72604 \
	"

STB_PLATFORM = "gb72604"
