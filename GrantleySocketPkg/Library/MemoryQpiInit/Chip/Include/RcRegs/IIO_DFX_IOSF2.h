/* Date Stamp: 8/23/2014 */

#ifndef IIO_DFX_IOSF2_h
#define IIO_DFX_IOSF2_h

#include "DataTypes.h"

/* Device and Function specifications:                                        */
/* For BDX_HOST:                                                              */
/* IIO_DFX_IOSF2_BDX_DEV 6                                                    */
/* IIO_DFX_IOSF2_BDX_FUN 5                                                    */

/* VID_IIO_DFX_IOSF2_REG supported on:                                        */
/*       BDX (0x20035000)                                                     */
/* Register default value:              0x8086                                */
#define VID_IIO_DFX_IOSF2_REG 0x16022000

#ifdef BDX_HOST
#ifndef ASM_INC
/* Struct format extracted from XML file BDX\0.6.5.IOSF.xml.
 * generated by critter 06_5_0x000
 */
typedef union {
  struct {
    UINT16 vendor_identification_number : 16;
    /* vendor_identification_number - Bits[15:0], RO, default = 16'b1000000010000110 
       The value is assigned by PCI-SIG to Intel.
     */
  } Bits;
  UINT16 Data;
} VID_IIO_DFX_IOSF2_STRUCT;
#endif /* ASM_INC */
#endif /*BDX_HOST */


/* DID_IIO_DFX_IOSF2_REG supported on:                                        */
/*       BDX (0x20035002)                                                     */
/* Register default value:              0x6F15                                */
#define DID_IIO_DFX_IOSF2_REG 0x16022002

#ifdef BDX_HOST
#ifndef ASM_INC
/* Struct format extracted from XML file BDX\0.6.5.IOSF.xml.
 * generated by critter 06_5_0x002
 */
typedef union {
  struct {
    UINT16 device_identification_number : 16;
    /* device_identification_number - Bits[15:0], RO, default = 16'b0110111100010101 
       Device ID values vary from function to function. Bits 15:8 are equal to 0x6F for 
       the processor. The following list is a breakdown of the function groups. 
       0x6F00 - 0x6F1F : PCI Express and DMI ports
       0x6F20 - 0x6F3F : IO Features (Intel QuickData Technology, APIC, VT, RAS, Intel 
       TXT) 
       0x6F40 - 0x6F5F : Performance Monitors
       0x6F60 - 0x6F7F : DFX
       0x6F80 - 0x6F9F : Intel QPI
       0x6FA0 - 0x6FBF : Home Agent/Memory Controller
       0x6FC0 - 0x6FDF : Power Management
       0x6FE0 - 0x6FFF : Cbo/Ring
       
       Default value may vary based on bus, device, and function of this CSR location.
     */
  } Bits;
  UINT16 Data;
} DID_IIO_DFX_IOSF2_STRUCT;
#endif /* ASM_INC */
#endif /*BDX_HOST */


/* PCICMD_IIO_DFX_IOSF2_REG supported on:                                     */
/*       BDX (0x20035004)                                                     */
/* Register default value:              0x0000                                */
#define PCICMD_IIO_DFX_IOSF2_REG 0x16022004

#ifdef BDX_HOST
#ifndef ASM_INC
/* Struct format extracted from XML file BDX\0.6.5.IOSF.xml.
 * generated by critter 06_5_0x004
 */
typedef union {
  struct {
    UINT16 iose : 1;
    /* iose - Bits[0:0], RO, default = 1'b0 
       1
     */
    UINT16 mse : 1;
    /* mse - Bits[1:1], RO, default = 1'b0 
       1
     */
    UINT16 bme : 1;
    /* bme - Bits[2:2], RO, default = 1'b0 
       1
     */
    UINT16 sce : 1;
    /* sce - Bits[3:3], RO, default = 1'b0 
       1
     */
    UINT16 mwie : 1;
    /* mwie - Bits[4:4], RO, default = 1'b0 
       1
     */
    UINT16 vga_palette_snoop_enable : 1;
    /* vga_palette_snoop_enable - Bits[5:5], RO, default = 1'b0 
       Not applicable to internal devices. Hardwired to 0.
     */
    UINT16 perre : 1;
    /* perre - Bits[6:6], RW, default = 1'b0 
       1
     */
    UINT16 idsel_stepping_wait_cycle_control : 1;
    /* idsel_stepping_wait_cycle_control - Bits[7:7], RO, default = 1'b0 
       Not applicable to internal devices. Hardwired to 0.
     */
    UINT16 serre : 1;
    /* serre - Bits[8:8], RW, default = 1'b0 
       1
     */
    UINT16 fast_back_to_back_enable : 1;
    /* fast_back_to_back_enable - Bits[9:9], RO, default = 1'b0 
       Not applicable to PCI Express and is hardwired to 0
     */
    UINT16 intx_interrupt_disable : 1;
    /* intx_interrupt_disable - Bits[10:10], RO, default = 1'b0 
       1
     */
    UINT16 rsvd : 5;
    /* rsvd - Bits[15:11], n/a, default = n/a 
       Padding added by header generation tool.
     */
  } Bits;
  UINT16 Data;
} PCICMD_IIO_DFX_IOSF2_STRUCT;
#endif /* ASM_INC */
#endif /*BDX_HOST */


/* PCISTS_IIO_DFX_IOSF2_REG supported on:                                     */
/*       BDX (0x20035006)                                                     */
/* Register default value:              0x0010                                */
#define PCISTS_IIO_DFX_IOSF2_REG 0x16022006

#ifdef BDX_HOST
#ifndef ASM_INC
/* Struct format extracted from XML file BDX\0.6.5.IOSF.xml.
 * generated by critter 06_5_0x006
 */
typedef union {
  struct {
    UINT16 rsvd_0 : 3;
    /* rsvd_0 - Bits[2:0], n/a, default = n/a 
       Padding added by header generation tool.
     */
    UINT16 intxstat : 1;
    /* intxstat - Bits[3:3], RO, default = 1'b0 
       1
     */
    UINT16 capl : 1;
    /* capl - Bits[4:4], RO, default = 1'b1 
       1
     */
    UINT16 pci66mhz_capable : 1;
    /* pci66mhz_capable - Bits[5:5], RO, default = 1'b0 
       Not applicable to PCI Express. Hardwired to 0.
     */
    UINT16 rsvd_6 : 1;
    /* rsvd_6 - Bits[6:6], n/a, default = n/a 
       Padding added by header generation tool.
     */
    UINT16 fb2b : 1;
    /* fb2b - Bits[7:7], RO, default = 1'b0 
       1
     */
    UINT16 mdpe : 1;
    /* mdpe - Bits[8:8], RO, default = 1'b0 
       1
     */
    UINT16 devselt : 2;
    /* devselt - Bits[10:9], RO, default = 2'b00 
       1
     */
    UINT16 sta : 1;
    /* sta - Bits[11:11], RO, default = 1'b0 
       1
     */
    UINT16 rta : 1;
    /* rta - Bits[12:12], RO, default = 1'b0 
       1
     */
    UINT16 rma : 1;
    /* rma - Bits[13:13], RO, default = 1'b0 
       1
     */
    UINT16 sse : 1;
    /* sse - Bits[14:14], RO, default = 1'b0 
       1
     */
    UINT16 dpe : 1;
    /* dpe - Bits[15:15], RO, default = 1'b0 
       1
     */
  } Bits;
  UINT16 Data;
} PCISTS_IIO_DFX_IOSF2_STRUCT;
#endif /* ASM_INC */
#endif /*BDX_HOST */


/* RID_IIO_DFX_IOSF2_REG supported on:                                        */
/*       BDX (0x10035008)                                                     */
/* Register default value:              0x00                                  */
#define RID_IIO_DFX_IOSF2_REG 0x16021008

#ifdef BDX_HOST
#ifndef ASM_INC
/* Struct format extracted from XML file BDX\0.6.5.IOSF.xml.
 * "PCIe header Revision ID register"
 */
typedef union {
  struct {
    UINT8 revision_id : 8;
    /* revision_id - Bits[7:0], ROS_V, default = 8'b00000000 
       Reflects the Uncore Revision ID after reset.
       Reflects the Compatibility Revision ID after BIOS writes 0x69 to any RID 
       register in the processor uncore. 
       
     */
  } Bits;
  UINT8 Data;
} RID_IIO_DFX_IOSF2_STRUCT;
#endif /* ASM_INC */
#endif /*BDX_HOST */


/* CCR_N0_IIO_DFX_IOSF2_REG supported on:                                     */
/*       BDX (0x10035009)                                                     */
/* Register default value:              0x00                                  */
#define CCR_N0_IIO_DFX_IOSF2_REG 0x16021009

#ifdef BDX_HOST
#ifndef ASM_INC
/* Struct format extracted from XML file BDX\0.6.5.IOSF.xml.
 * PCIe header ClassCode register
 */
typedef union {
  struct {
    UINT8 register_level_programming_interface : 8;
    /* register_level_programming_interface - Bits[7:0], RO_V, default = 8'b00000000  */
  } Bits;
  UINT8 Data;
} CCR_N0_IIO_DFX_IOSF2_STRUCT;
#endif /* ASM_INC */
#endif /*BDX_HOST */


/* CCR_N1_IIO_DFX_IOSF2_REG supported on:                                     */
/*       BDX (0x2003500A)                                                     */
/* Register default value:              0x0880                                */
#define CCR_N1_IIO_DFX_IOSF2_REG 0x1602200A

#ifdef BDX_HOST
#ifndef ASM_INC
/* Struct format extracted from XML file BDX\0.6.5.IOSF.xml.
 * PCIe header ClassCode register
 */
typedef union {
  struct {
    UINT16 sub_class : 8;
    /* sub_class - Bits[7:0], RO_V, default = 8'b10000000 
       The value changes dependent upon the dev/func accessed. A table of the values 
       can be found in the Class-code tab of the msgch spread-sheet  
          Most dev-func will return 8'h80 for this field except for the following 
       dev-func0,func1,... combinations. The following exceptions will return 8'h01. 
                 dev-0x0 through 0x7 (return 0x4, d0f0 return 0x0 under default 
       settings) 
       	  dev-0x8 func-2
       	  dev-0x9 func-2
       	  dev-0xA func-2
       	  dev-0xB func-1,2,5,6
       	  dev-0x10 func-1,6
       	  dev-0x12 func-1,5
       	  
     */
    UINT16 base_class : 8;
    /* base_class - Bits[15:8], RO_V, default = 8'b00001000 
       The value changes dependent upon the dev-func accessed. A table of the values 
       can be found in the Class-code tab of the msgch spread-sheet  
          Most dev-func will return 8'h08 for this field except for the following 
       dev-func0,func1,... combinations. The following exceptions will return 8'h11. 
                 dev-0x0 through 0x7 (return 0x6)
       	  dev-0x8 func-2
       	  dev-0x9 func-2
       	  dev-0xA func-2
       	  dev-0xB func-1,2,5,6
       	  dev-0x10 func-1,6
       	  dev-0x12 func-1,5
       	  
     */
  } Bits;
  UINT16 Data;
} CCR_N1_IIO_DFX_IOSF2_STRUCT;
#endif /* ASM_INC */
#endif /*BDX_HOST */


/* CLSR_IIO_DFX_IOSF2_REG supported on:                                       */
/*       BDX (0x1003500C)                                                     */
/* Register default value:              0x00                                  */
#define CLSR_IIO_DFX_IOSF2_REG 0x1602100C

#ifdef BDX_HOST
#ifndef ASM_INC
/* Struct format extracted from XML file BDX\0.6.5.IOSF.xml.
 * generated by critter 06_5_0x00c
 */
typedef union {
  struct {
    UINT8 cacheline_size : 8;
    /* cacheline_size - Bits[7:0], RW, default = 8'b00000000  */
  } Bits;
  UINT8 Data;
} CLSR_IIO_DFX_IOSF2_STRUCT;
#endif /* ASM_INC */
#endif /*BDX_HOST */


/* PLAT_IIO_DFX_IOSF2_REG supported on:                                       */
/*       BDX (0x1003500D)                                                     */
/* Register default value:              0x00                                  */
#define PLAT_IIO_DFX_IOSF2_REG 0x1602100D

#ifdef BDX_HOST
#ifndef ASM_INC
/* Struct format extracted from XML file BDX\0.6.5.IOSF.xml.
 * generated by critter 06_5_0x00d
 */
typedef union {
  struct {
    UINT8 primary_latency_timer : 8;
    /* primary_latency_timer - Bits[7:0], RO, default = 8'b00000000 
       Not applicable to PCI-Express. Hardwired to 00h.
     */
  } Bits;
  UINT8 Data;
} PLAT_IIO_DFX_IOSF2_STRUCT;
#endif /* ASM_INC */
#endif /*BDX_HOST */


/* HDR_IIO_DFX_IOSF2_REG supported on:                                        */
/*       BDX (0x1003500E)                                                     */
/* Register default value:              0x80                                  */
#define HDR_IIO_DFX_IOSF2_REG 0x1602100E

#ifdef BDX_HOST
#ifndef ASM_INC
/* Struct format extracted from XML file BDX\0.6.5.IOSF.xml.
 * generated by critter 06_5_0x00e
 */
typedef union {
  struct {
    UINT8 configuration_layout : 7;
    /* configuration_layout - Bits[6:0], RO, default = 7'b0000000 
       This field identifies the format of the configuration header layout. It is Type 
       0 for all these devices. The default is 00h, indicating a 'endpoint device'. 
     */
    UINT8 multi_function_device : 1;
    /* multi_function_device - Bits[7:7], RO, default = 1'b1 
       This bit defaults to 1b since all these devices are multi-function
     */
  } Bits;
  UINT8 Data;
} HDR_IIO_DFX_IOSF2_STRUCT;
#endif /* ASM_INC */
#endif /*BDX_HOST */


/* BIST_IIO_DFX_IOSF2_REG supported on:                                       */
/*       BDX (0x1003500F)                                                     */
/* Register default value:              0x00                                  */
#define BIST_IIO_DFX_IOSF2_REG 0x1602100F

#ifdef BDX_HOST
#ifndef ASM_INC
/* Struct format extracted from XML file BDX\0.6.5.IOSF.xml.
 * generated by critter 06_5_0x00f
 */
typedef union {
  struct {
    UINT8 bist_tests : 8;
    /* bist_tests - Bits[7:0], RO, default = 8'b00000000 
       Not supported. Hardwired to 00h
     */
  } Bits;
  UINT8 Data;
} BIST_IIO_DFX_IOSF2_STRUCT;
#endif /* ASM_INC */
#endif /*BDX_HOST */


/* SVID_IIO_DFX_IOSF2_REG supported on:                                       */
/*       BDX (0x2003502C)                                                     */
/* Register default value:              0x8086                                */
#define SVID_IIO_DFX_IOSF2_REG 0x1602202C

#ifdef BDX_HOST
#ifndef ASM_INC
/* Struct format extracted from XML file BDX\0.6.5.IOSF.xml.
 * generated by critter 06_5_0x02c
 */
typedef union {
  struct {
    UINT16 subsystem_vendor_identification_number : 16;
    /* subsystem_vendor_identification_number - Bits[15:0], RW_O, default = 16'b1000000010000110 
       The default value specifies Intel but can be set to any value once after reset.
     */
  } Bits;
  UINT16 Data;
} SVID_IIO_DFX_IOSF2_STRUCT;
#endif /* ASM_INC */
#endif /*BDX_HOST */


/* SDID_IIO_DFX_IOSF2_REG supported on:                                       */
/*       BDX (0x2003502E)                                                     */
/* Register default value:              0x0000                                */
#define SDID_IIO_DFX_IOSF2_REG 0x1602202E

#ifdef BDX_HOST
#ifndef ASM_INC
/* Struct format extracted from XML file BDX\0.6.5.IOSF.xml.
 * generated by critter 06_5_0x02e
 */
typedef union {
  struct {
    UINT16 subsystem_device_identification_number : 16;
    /* subsystem_device_identification_number - Bits[15:0], RW_O, default = 16'b0000000000000000 
       Assigned by the subsystem vendor to uniquely identify the subsystem
     */
  } Bits;
  UINT16 Data;
} SDID_IIO_DFX_IOSF2_STRUCT;
#endif /* ASM_INC */
#endif /*BDX_HOST */


/* CAPPTR_IIO_DFX_IOSF2_REG supported on:                                     */
/*       BDX (0x10035034)                                                     */
/* Register default value:              0x40                                  */
#define CAPPTR_IIO_DFX_IOSF2_REG 0x16021034

#ifdef BDX_HOST
#ifndef ASM_INC
/* Struct format extracted from XML file BDX\0.6.5.IOSF.xml.
 * generated by critter 06_5_0x034
 */
typedef union {
  struct {
    UINT8 capability_pointer : 8;
    /* capability_pointer - Bits[7:0], RO, default = 8'b01000000 
       Points to the first capability structure for the device which is the PCIe 
       capability. 
     */
  } Bits;
  UINT8 Data;
} CAPPTR_IIO_DFX_IOSF2_STRUCT;
#endif /* ASM_INC */
#endif /*BDX_HOST */


/* INTL_IIO_DFX_IOSF2_REG supported on:                                       */
/*       BDX (0x1003503C)                                                     */
/* Register default value:              0x00                                  */
#define INTL_IIO_DFX_IOSF2_REG 0x1602103C

#ifdef BDX_HOST
#ifndef ASM_INC
/* Struct format extracted from XML file BDX\0.6.5.IOSF.xml.
 * generated by critter 06_5_0x03c
 */
typedef union {
  struct {
    UINT8 interrupt_line : 8;
    /* interrupt_line - Bits[7:0], RO, default = 8'b00000000 
       N/A for these devices
     */
  } Bits;
  UINT8 Data;
} INTL_IIO_DFX_IOSF2_STRUCT;
#endif /* ASM_INC */
#endif /*BDX_HOST */


/* INTPIN_IIO_DFX_IOSF2_REG supported on:                                     */
/*       BDX (0x1003503D)                                                     */
/* Register default value:              0x00                                  */
#define INTPIN_IIO_DFX_IOSF2_REG 0x1602103D

#ifdef BDX_HOST
#ifndef ASM_INC
/* Struct format extracted from XML file BDX\0.6.5.IOSF.xml.
 * generated by critter 06_5_0x03d
 */
typedef union {
  struct {
    UINT8 interrupt_pin : 8;
    /* interrupt_pin - Bits[7:0], RO, default = 8'b00000000 
       N/A since these devices do not generate any interrupt on their own
     */
  } Bits;
  UINT8 Data;
} INTPIN_IIO_DFX_IOSF2_STRUCT;
#endif /* ASM_INC */
#endif /*BDX_HOST */


/* MINGNT_IIO_DFX_IOSF2_REG supported on:                                     */
/*       BDX (0x1003503E)                                                     */
/* Register default value:              0x00                                  */
#define MINGNT_IIO_DFX_IOSF2_REG 0x1602103E

#ifdef BDX_HOST
#ifndef ASM_INC
/* Struct format extracted from XML file BDX\0.6.5.IOSF.xml.
 * generated by critter 06_5_0x03e
 */
typedef union {
  struct {
    UINT8 mgv : 8;
    /* mgv - Bits[7:0], RO, default = 8'b00000000 
       The Device does not burst as a PCI compliant master.
     */
  } Bits;
  UINT8 Data;
} MINGNT_IIO_DFX_IOSF2_STRUCT;
#endif /* ASM_INC */
#endif /*BDX_HOST */


/* MAXLAT_IIO_DFX_IOSF2_REG supported on:                                     */
/*       BDX (0x1003503F)                                                     */
/* Register default value:              0x00                                  */
#define MAXLAT_IIO_DFX_IOSF2_REG 0x1602103F

#ifdef BDX_HOST
#ifndef ASM_INC
/* Struct format extracted from XML file BDX\0.6.5.IOSF.xml.
 * generated by critter 06_5_0x03f
 */
typedef union {
  struct {
    UINT8 mlv : 8;
    /* mlv - Bits[7:0], RO, default = 8'b00000000 
       The Device has no specific requirements for how often it needs to access the PCI 
       bus. 
     */
  } Bits;
  UINT8 Data;
} MAXLAT_IIO_DFX_IOSF2_STRUCT;
#endif /* ASM_INC */
#endif /*BDX_HOST */


/* PXPCAP_IIO_DFX_IOSF2_REG supported on:                                     */
/*       BDX (0x40035040)                                                     */
/* Register default value:              0x00920010                            */
#define PXPCAP_IIO_DFX_IOSF2_REG 0x16024040

#ifdef BDX_HOST
#ifndef ASM_INC
/* Struct format extracted from XML file BDX\0.6.5.IOSF.xml.
 * generated by critter 06_5_0x040
 */
typedef union {
  struct {
    UINT32 capability_id : 8;
    /* capability_id - Bits[7:0], RO, default = 8'b00010000 
       Provides the PCI Express capability ID assigned by PCI-SIG.
     */
    UINT32 next_ptr : 8;
    /* next_ptr - Bits[15:8], RO, default = 8'b00000000 
       Pointer to the next capability. Set to 0 to indicate there are no more 
       capability structures. 
     */
    UINT32 capability_version : 4;
    /* capability_version - Bits[19:16], RO, default = 4'b0010 
       PCI Express Capability is Compliant with Version 1.0 of the PCI Express Spec.
       
       Note:
       This capability structure is not compliant with Versions beyond 1.0, since they 
       require additional capability registers to be reserved. The only purpose for 
       this capability structure is to make enhanced configuration space available. 
       Minimizing the size of this structure is accomplished by reporting version 1.0 
       compliancy and reporting that this is an integrated root port device. As such, 
       only three Dwords of configuration space are required for this structure. 
     */
    UINT32 device_port_type : 4;
    /* device_port_type - Bits[23:20], RO, default = 4'b1001 
       Device type is Root Complex Integrated Endpoint
     */
    UINT32 slot_implemented : 1;
    /* slot_implemented - Bits[24:24], RO, default = 1'b0 
       N/A for integrated endpoints
     */
    UINT32 interrupt_message_number : 5;
    /* interrupt_message_number - Bits[29:25], RO, default = 5'b00000 
       N/A for this device
     */
    UINT32 rsvd : 2;
    /* rsvd - Bits[31:30], n/a, default = n/a 
       Padding added by header generation tool.
     */
  } Bits;
  UINT32 Data;
} PXPCAP_IIO_DFX_IOSF2_STRUCT;
#endif /* ASM_INC */
#endif /*BDX_HOST */


/* DEVCAP_IIO_DFX_IOSF2_REG supported on:                                     */
/*       BDX (0x40035044)                                                     */
/* Register default value:              0x00008000                            */
#define DEVCAP_IIO_DFX_IOSF2_REG 0x16024044

#ifdef BDX_HOST
#ifndef ASM_INC
/* Struct format extracted from XML file BDX\0.6.5.IOSF.xml.
 * generated by critter 06_5_0x044
 */
typedef union {
  struct {
    UINT32 max_payload_size_supported : 3;
    /* max_payload_size_supported - Bits[2:0], RO, default = 3'b000  */
    UINT32 phantom_functions_supported : 2;
    /* phantom_functions_supported - Bits[4:3], RO, default = 2'b00  */
    UINT32 extended_tag_field_supported : 1;
    /* extended_tag_field_supported - Bits[5:5], RO, default = 1'b0  */
    UINT32 endpoint_l0s_acceptable_latency : 3;
    /* endpoint_l0s_acceptable_latency - Bits[8:6], RO, default = 3'b000  */
    UINT32 endpoint_l1_acceptable_latency : 3;
    /* endpoint_l1_acceptable_latency - Bits[11:9], RO, default = 3'b000  */
    UINT32 attention_button_present : 1;
    /* attention_button_present - Bits[12:12], RO, default = 1'b0  */
    UINT32 attention_indicator_present : 1;
    /* attention_indicator_present - Bits[13:13], RO, default = 1'b0  */
    UINT32 power_indicator_present_on_device : 1;
    /* power_indicator_present_on_device - Bits[14:14], RO, default = 1'b0  */
    UINT32 role_based_error_reporting : 1;
    /* role_based_error_reporting - Bits[15:15], RO, default = 1'b1  */
    UINT32 rsvd_16 : 2;
    /* rsvd_16 - Bits[17:16], n/a, default = n/a 
       Padding added by header generation tool.
     */
    UINT32 captured_slot_power_limit_value : 8;
    /* captured_slot_power_limit_value - Bits[25:18], RO, default = 8'b00000000  */
    UINT32 captured_slot_power_limit_scale : 2;
    /* captured_slot_power_limit_scale - Bits[27:26], RO, default = 2'b00  */
    UINT32 rsvd_28 : 4;
    /* rsvd_28 - Bits[31:28], n/a, default = n/a 
       Padding added by header generation tool.
     */
  } Bits;
  UINT32 Data;
} DEVCAP_IIO_DFX_IOSF2_STRUCT;
#endif /* ASM_INC */
#endif /*BDX_HOST */


/* DEVCON_IIO_DFX_IOSF2_REG supported on:                                     */
/*       BDX (0x20035048)                                                     */
/* Register default value:              0x0000                                */
#define DEVCON_IIO_DFX_IOSF2_REG 0x16022048

#ifdef BDX_HOST
#ifndef ASM_INC
/* Struct format extracted from XML file BDX\0.6.5.IOSF.xml.
 * The PCI Express Device Control register controls PCI Express specific 
 * capabilities parameters associated with the device. 
 */
typedef union {
  struct {
    UINT16 correctable_error_reporting_enable : 1;
    /* correctable_error_reporting_enable - Bits[0:0], RO, default = 1'b0 
       N/A for CB DMA
     */
    UINT16 non_fatal_error_reporting_enable : 1;
    /* non_fatal_error_reporting_enable - Bits[1:1], RO, default = 1'b0 
       N/A for CB DMA
     */
    UINT16 fatal_error_reporting_enable : 1;
    /* fatal_error_reporting_enable - Bits[2:2], RO, default = 1'b0 
       N/A for CB DMA
     */
    UINT16 unsupported_request_reporting_enable : 1;
    /* unsupported_request_reporting_enable - Bits[3:3], RO, default = 1'b0 
       N/A for CB DMA
     */
    UINT16 enable_relaxed_ordering : 1;
    /* enable_relaxed_ordering - Bits[4:4], RO, default = 1'b0 
       For most parts, writes from CB DMA are relaxed ordered, except for DMA 
       completion writes. But the fact that CB DMA writes are relaxed ordered is not 
       very useful except when the writes are also non-snooped. If the writes are 
       snooped, relaxed ordering does not provide any particular advantage based on IIO 
       uArch. But when writes are non-snooped, relaxed ordering is required to get good 
       BW and this bit is expected to be set. If this bit is clear, NS writes will get 
       very poor performance. 
     */
    UINT16 max_payload_size : 3;
    /* max_payload_size - Bits[7:5], RO, default = 3'b000 
       N/A for CB DMA
     */
    UINT16 extended_tag_field_enable : 1;
    /* extended_tag_field_enable - Bits[8:8], RO, default = 1'b0  */
    UINT16 phantom_functions_enable : 1;
    /* phantom_functions_enable - Bits[9:9], RO, default = 1'b0 
       Not applicable to CB DMA since it never uses phantom functions as a requester.
     */
    UINT16 auxiliary_power_management_enable : 1;
    /* auxiliary_power_management_enable - Bits[10:10], RO, default = 1'b0 
       Not applicable to CB DMA
     */
    UINT16 enable_no_snoop : 1;
    /* enable_no_snoop - Bits[11:11], RO, default = 1'b0 
       For CB DMA, when this bit is clear, all DMA transactions must be snooped. When 
       set, DMA transactions to main memory can utilize No Snoop optimization under the 
       guidance of the device driver. 
     */
    UINT16 max_read_request_size : 3;
    /* max_read_request_size - Bits[14:12], RO, default = 3'b000 
       N/A to CB DMA since it does not issue tx on PCIE
     */
    UINT16 rsvd : 1;
    /* rsvd - Bits[15:15], n/a, default = n/a 
       Padding added by header generation tool.
     */
  } Bits;
  UINT16 Data;
} DEVCON_IIO_DFX_IOSF2_STRUCT;
#endif /* ASM_INC */
#endif /*BDX_HOST */


/* DEVSTS_IIO_DFX_IOSF2_REG supported on:                                     */
/*       BDX (0x2003504A)                                                     */
/* Register default value:              0x0000                                */
#define DEVSTS_IIO_DFX_IOSF2_REG 0x1602204A

#ifdef BDX_HOST
#ifndef ASM_INC
/* Struct format extracted from XML file BDX\0.6.5.IOSF.xml.
 * generated by critter 06_5_0x04a
 */
typedef union {
  struct {
    UINT16 correctable_error_detected : 1;
    /* correctable_error_detected - Bits[0:0], RO, default = 1'b0  */
    UINT16 non_fatal_error_detected : 1;
    /* non_fatal_error_detected - Bits[1:1], RO, default = 1'b0  */
    UINT16 fatal_error_detected : 1;
    /* fatal_error_detected - Bits[2:2], RO, default = 1'b0  */
    UINT16 unsupported_request_detected : 1;
    /* unsupported_request_detected - Bits[3:3], RO, default = 1'b0  */
    UINT16 aux_power_detected : 1;
    /* aux_power_detected - Bits[4:4], RO, default = 1'b0  */
    UINT16 transactions_pending : 1;
    /* transactions_pending - Bits[5:5], RO, default = 1'b0  */
    UINT16 rsvd : 10;
    /* rsvd - Bits[15:6], n/a, default = n/a 
       Padding added by header generation tool.
     */
  } Bits;
  UINT16 Data;
} DEVSTS_IIO_DFX_IOSF2_STRUCT;
#endif /* ASM_INC */
#endif /*BDX_HOST */


/* LNKCAP_IIO_DFX_IOSF2_REG supported on:                                     */
/*       BDX (0x4003504C)                                                     */
/* Register default value:              0x003BF400                            */
#define LNKCAP_IIO_DFX_IOSF2_REG 0x1602404C

#ifdef BDX_HOST
#ifndef ASM_INC
/* Struct format extracted from XML file BDX\0.6.5.IOSF.xml.
 * generated by critter 06_5_0x04c
 */
typedef union {
  struct {
    UINT32 link_speeds_supported : 4;
    /* link_speeds_supported - Bits[3:0], RO, default = 4'b0000  */
    UINT32 maximum_link_width : 6;
    /* maximum_link_width - Bits[9:4], RO, default = 6'b000000  */
    UINT32 active_state_link_pm_support : 2;
    /* active_state_link_pm_support - Bits[11:10], RO, default = 2'b01  */
    UINT32 l0s_exit_latency : 3;
    /* l0s_exit_latency - Bits[14:12], RO, default = 3'b111  */
    UINT32 l1_exit_latency : 3;
    /* l1_exit_latency - Bits[17:15], RO, default = 3'b111  */
    UINT32 clock_power_management : 1;
    /* clock_power_management - Bits[18:18], RO, default = 1'b0  */
    UINT32 surprise_down_error_reporting_capable : 1;
    /* surprise_down_error_reporting_capable - Bits[19:19], RO, default = 1'b1  */
    UINT32 data_link_layer_link_active : 1;
    /* data_link_layer_link_active - Bits[20:20], RO, default = 1'b1  */
    UINT32 link_bandwidth_notification_capability_a : 1;
    /* link_bandwidth_notification_capability_a - Bits[21:21], RO, default = 1'b1  */
    UINT32 rsvd : 2;
    /* rsvd - Bits[23:22], n/a, default = n/a 
       Padding added by header generation tool.
     */
    UINT32 port_number : 8;
    /* port_number - Bits[31:24], RO, default = 8'b00000000  */
  } Bits;
  UINT32 Data;
} LNKCAP_IIO_DFX_IOSF2_STRUCT;
#endif /* ASM_INC */
#endif /*BDX_HOST */


/* LNKSTS_IIO_DFX_IOSF2_REG supported on:                                     */
/*       BDX (0x20035052)                                                     */
/* Register default value:              0x1000                                */
#define LNKSTS_IIO_DFX_IOSF2_REG 0x16022052

#ifdef BDX_HOST
#ifndef ASM_INC
/* Struct format extracted from XML file BDX\0.6.5.IOSF.xml.
 * generated by critter 06_5_0x052
 */
typedef union {
  struct {
    UINT16 current_link_speed : 4;
    /* current_link_speed - Bits[3:0], RO, default = 4'b0000  */
    UINT16 negotiated_link_width : 6;
    /* negotiated_link_width - Bits[9:4], RO, default = 6'b000000  */
    UINT16 rsvd : 1;
    /* rsvd - Bits[10:10], n/a, default = n/a 
       Padding added by header generation tool.
     */
    UINT16 link_training : 1;
    /* link_training - Bits[11:11], RO, default = 1'b0  */
    UINT16 slot_clock_configuration : 1;
    /* slot_clock_configuration - Bits[12:12], RO, default = 1'b1  */
    UINT16 data_link_layer_link_active : 1;
    /* data_link_layer_link_active - Bits[13:13], RO, default = 1'b0  */
    UINT16 link_bandwidth_management_status_this : 1;
    /* link_bandwidth_management_status_this - Bits[14:14], RO, default = 1'b0  */
    UINT16 link_autonomous_bandwidth_status_this : 1;
    /* link_autonomous_bandwidth_status_this - Bits[15:15], RO, default = 1'b0  */
  } Bits;
  UINT16 Data;
} LNKSTS_IIO_DFX_IOSF2_STRUCT;
#endif /* ASM_INC */
#endif /*BDX_HOST */


/* LNKCAP2_IIO_DFX_IOSF2_REG supported on:                                    */
/*       BDX (0x4003506C)                                                     */
/* Register default value:              0x003BF400                            */
#define LNKCAP2_IIO_DFX_IOSF2_REG 0x1602406C

#ifdef BDX_HOST
#ifndef ASM_INC
/* Struct format extracted from XML file BDX\0.6.5.IOSF.xml.
 * generated by critter 06_5_0x06c
 */
typedef union {
  struct {
    UINT32 link_speeds_supported : 4;
    /* link_speeds_supported - Bits[3:0], RO, default = 4'b0000  */
    UINT32 maximum_link_width : 6;
    /* maximum_link_width - Bits[9:4], RO, default = 6'b000000  */
    UINT32 active_state_link_pm_support : 2;
    /* active_state_link_pm_support - Bits[11:10], RO, default = 2'b01  */
    UINT32 l0s_exit_latency : 3;
    /* l0s_exit_latency - Bits[14:12], RO, default = 3'b111  */
    UINT32 l1_exit_latency : 3;
    /* l1_exit_latency - Bits[17:15], RO, default = 3'b111  */
    UINT32 clock_power_management : 1;
    /* clock_power_management - Bits[18:18], RO, default = 1'b0  */
    UINT32 surprise_down_error_reporting_capable : 1;
    /* surprise_down_error_reporting_capable - Bits[19:19], RO, default = 1'b1  */
    UINT32 data_link_layer_link_active : 1;
    /* data_link_layer_link_active - Bits[20:20], RO, default = 1'b1  */
    UINT32 link_bandwidth_notification_capability_a : 1;
    /* link_bandwidth_notification_capability_a - Bits[21:21], RO, default = 1'b1  */
    UINT32 rsvd : 2;
    /* rsvd - Bits[23:22], n/a, default = n/a 
       Padding added by header generation tool.
     */
    UINT32 port_number : 8;
    /* port_number - Bits[31:24], RO, default = 8'b00000000  */
  } Bits;
  UINT32 Data;
} LNKCAP2_IIO_DFX_IOSF2_STRUCT;
#endif /* ASM_INC */
#endif /*BDX_HOST */


/* LNKCON2_OLD_IIO_DFX_IOSF2_REG supported on:                                */
/*       BDX (0x20035070)                                                     */
/* Register default value:              0x0000                                */
#define LNKCON2_OLD_IIO_DFX_IOSF2_REG 0x16022070

#ifdef BDX_HOST
#ifndef ASM_INC
/* Struct format extracted from XML file BDX\0.6.5.IOSF.xml.
 * generated by critter 06_5_0x070
 */
typedef union {
  struct {
    UINT16 active_state_link_pm_control : 2;
    /* active_state_link_pm_control - Bits[1:0], RO, default = 2'b00  */
    UINT16 rsvd_2 : 1;
    /* rsvd_2 - Bits[2:2], n/a, default = n/a 
       Padding added by header generation tool.
     */
    UINT16 read_completion_boundary : 1;
    /* read_completion_boundary - Bits[3:3], RO, default = 1'b0  */
    UINT16 link_disable : 1;
    /* link_disable - Bits[4:4], RO, default = 1'b0  */
    UINT16 retrain_link : 1;
    /* retrain_link - Bits[5:5], RO, default = 1'b0  */
    UINT16 common_clock_configuration : 1;
    /* common_clock_configuration - Bits[6:6], RO, default = 1'b0  */
    UINT16 extended_synch : 1;
    /* extended_synch - Bits[7:7], RO, default = 1'b0  */
    UINT16 enable_clock_power_management_na : 1;
    /* enable_clock_power_management_na - Bits[8:8], RO, default = 1'b0  */
    UINT16 hardware_autonomous_width_disable_ioh : 1;
    /* hardware_autonomous_width_disable_ioh - Bits[9:9], RO, default = 1'b0  */
    UINT16 link_bandwidth_management_interrupt_enable : 1;
    /* link_bandwidth_management_interrupt_enable - Bits[10:10], RO, default = 1'b0  */
    UINT16 link_autonomous_bandwidth_interrupt_enable : 1;
    /* link_autonomous_bandwidth_interrupt_enable - Bits[11:11], RO, default = 1'b0  */
    UINT16 rsvd_12 : 4;
    /* rsvd_12 - Bits[15:12], n/a, default = n/a 
       Padding added by header generation tool.
     */
  } Bits;
  UINT16 Data;
} LNKCON2_OLD_IIO_DFX_IOSF2_STRUCT;
#endif /* ASM_INC */
#endif /*BDX_HOST */


/* LNKSTS2_IIO_DFX_IOSF2_REG supported on:                                    */
/*       BDX (0x20035072)                                                     */
/* Register default value:              0x1000                                */
#define LNKSTS2_IIO_DFX_IOSF2_REG 0x16022072

#ifdef BDX_HOST
#ifndef ASM_INC
/* Struct format extracted from XML file BDX\0.6.5.IOSF.xml.
 * generated by critter 06_5_0x072
 */
typedef union {
  struct {
    UINT16 current_link_speed : 4;
    /* current_link_speed - Bits[3:0], RO, default = 4'b0000  */
    UINT16 negotiated_link_width : 6;
    /* negotiated_link_width - Bits[9:4], RO, default = 6'b000000  */
    UINT16 rsvd : 1;
    /* rsvd - Bits[10:10], n/a, default = n/a 
       Padding added by header generation tool.
     */
    UINT16 link_training : 1;
    /* link_training - Bits[11:11], RO, default = 1'b0  */
    UINT16 slot_clock_configuration : 1;
    /* slot_clock_configuration - Bits[12:12], RO, default = 1'b1  */
    UINT16 data_link_layer_link_active : 1;
    /* data_link_layer_link_active - Bits[13:13], RO, default = 1'b0  */
    UINT16 link_bandwidth_management_status_this : 1;
    /* link_bandwidth_management_status_this - Bits[14:14], RO, default = 1'b0  */
    UINT16 link_autonomous_bandwidth_status_this : 1;
    /* link_autonomous_bandwidth_status_this - Bits[15:15], RO, default = 1'b0  */
  } Bits;
  UINT16 Data;
} LNKSTS2_IIO_DFX_IOSF2_STRUCT;
#endif /* ASM_INC */
#endif /*BDX_HOST */


/* SLTCAP2_IIO_DFX_IOSF2_REG supported on:                                    */
/*       BDX (0x40035074)                                                     */
/* Register default value:              0x00000000                            */
#define SLTCAP2_IIO_DFX_IOSF2_REG 0x16024074

#ifdef BDX_HOST
#ifndef ASM_INC
/* Struct format extracted from XML file BDX\0.6.5.IOSF.xml.
 * generated by critter 06_5_0x074
 */
typedef union {
  struct {
    UINT32 attention_button_present : 1;
    /* attention_button_present - Bits[0:0], RO, default = 1'b0  */
    UINT32 power_controller_present : 1;
    /* power_controller_present - Bits[1:1], RO, default = 1'b0  */
    UINT32 mrl_sensor_present : 1;
    /* mrl_sensor_present - Bits[2:2], RO, default = 1'b0  */
    UINT32 attention_indicator_present : 1;
    /* attention_indicator_present - Bits[3:3], RO, default = 1'b0  */
    UINT32 power_indicator_present : 1;
    /* power_indicator_present - Bits[4:4], RO, default = 1'b0  */
    UINT32 hotplug_surprise : 1;
    /* hotplug_surprise - Bits[5:5], RO, default = 1'b0  */
    UINT32 hotplug_capable : 1;
    /* hotplug_capable - Bits[6:6], RO, default = 1'b0  */
    UINT32 slot_power_limit_value : 8;
    /* slot_power_limit_value - Bits[14:7], RO, default = 8'b00000000  */
    UINT32 slot_power_limit_scale : 2;
    /* slot_power_limit_scale - Bits[16:15], RO, default = 2'b00  */
    UINT32 electromechanical_interlock_present : 1;
    /* electromechanical_interlock_present - Bits[17:17], RO, default = 1'b0  */
    UINT32 command_complete_not_capable : 1;
    /* command_complete_not_capable - Bits[18:18], RO, default = 1'b0  */
    UINT32 physical_slot_number : 13;
    /* physical_slot_number - Bits[31:19], RO, default = 13'b0000000000000  */
  } Bits;
  UINT32 Data;
} SLTCAP2_IIO_DFX_IOSF2_STRUCT;
#endif /* ASM_INC */
#endif /*BDX_HOST */


/* SLTSTS2_IIO_DFX_IOSF2_REG supported on:                                    */
/*       BDX (0x2003507A)                                                     */
/* Register default value:              0x0000                                */
#define SLTSTS2_IIO_DFX_IOSF2_REG 0x1602207A

#ifdef BDX_HOST
#ifndef ASM_INC
/* Struct format extracted from XML file BDX\0.6.5.IOSF.xml.
 * generated by critter 06_5_0x07a
 */
typedef union {
  struct {
    UINT16 attention_button_pressed : 1;
    /* attention_button_pressed - Bits[0:0], RO, default = 1'b0  */
    UINT16 power_fault_detected : 1;
    /* power_fault_detected - Bits[1:1], RO, default = 1'b0  */
    UINT16 mrl_sensor_changed : 1;
    /* mrl_sensor_changed - Bits[2:2], RO, default = 1'b0  */
    UINT16 presence_detect_changed : 1;
    /* presence_detect_changed - Bits[3:3], RO, default = 1'b0  */
    UINT16 command_completed : 1;
    /* command_completed - Bits[4:4], RO, default = 1'b0  */
    UINT16 mrl_sensor_state : 1;
    /* mrl_sensor_state - Bits[5:5], RO, default = 1'b0  */
    UINT16 presence_detect_state : 1;
    /* presence_detect_state - Bits[6:6], RO, default = 1'b0  */
    UINT16 electromechanical_latch_status : 1;
    /* electromechanical_latch_status - Bits[7:7], RO, default = 1'b0  */
    UINT16 data_link_layer_state_changed : 1;
    /* data_link_layer_state_changed - Bits[8:8], RO, default = 1'b0  */
    UINT16 rsvd : 7;
    /* rsvd - Bits[15:9], n/a, default = n/a 
       Padding added by header generation tool.
     */
  } Bits;
  UINT16 Data;
} SLTSTS2_IIO_DFX_IOSF2_STRUCT;
#endif /* ASM_INC */
#endif /*BDX_HOST */














/* XPPRIVC1_IIO_DFX_IOSF2_REG supported on:                                   */
/*       BDX (0x4003526C)                                                     */
/* Register default value:              0x00000355                            */
#define XPPRIVC1_IIO_DFX_IOSF2_REG 0x1602426C

#ifdef BDX_HOST
#ifndef ASM_INC
/* Struct format extracted from XML file BDX\0.6.5.IOSF.xml.
 * generated by critter 06_5_0x26c
 */
typedef union {
  struct {
    UINT32 rsvd_0 : 4;
    UINT32 hpmsirevalen : 1;
    /* hpmsirevalen - Bits[4:4], RWS, default = 1'b1  */
    UINT32 hpmsiclapsen : 1;
    /* hpmsiclapsen - Bits[5:5], RWS, default = 1'b0 
       1
     */
    UINT32 rsvd_6 : 26;
  } Bits;
  UINT32 Data;
} XPPRIVC1_IIO_DFX_IOSF2_STRUCT;
#endif /* ASM_INC */
#endif /*BDX_HOST */






















#endif /* IIO_DFX_IOSF2_h */
