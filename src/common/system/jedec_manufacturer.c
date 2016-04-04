/*
 * Copyright (c) 2015 2016, Intel Corporation
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of Intel Corporation nor the names of its contributors
 *     may be used to endorse or promote products derived from this software
 *     without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * This file contains a method to lookup the Jedec standard manufacturer from the ID.
 * The strings come directly from the Jedec specification.
 */

#include "jedec_manufacturer.h"
#include <string/s_str.h>

#define	MAX_MANUFACTURER_BANKS	9

/*
 * From JEDEC JEP-106AN 1/2014
 * Bank 1 Manufacturers
 */
static const char *manufacturers_bank1[] =
{
	"AMD",
	"AMI",
	"Fairchild",
	"Fujitsu",
	"GTE",
	"Harris",
	"Hitachi",
	"Inmos",
	"Intel",
	"I.T.T.",
	"Intersil",
	"Monolithic Memories",
	"Mostek",
	"Freescale (former Motorola)",
	"National",
	"NEC",
	"RCA",
	"Raytheon",
	"Conexant (Rockwell)",
	"Seeq",
	"NXP",
	"Synertek",
	"Texas Instruments",
	"Toshiba",
	"Xicor",
	"Zilog",
	"Eurotechnique",
	"Mitsubishi",
	"Lucent (AT&T)",
	"Exel",
	"Atmel",
	"STMicroelectronics",
	"Lattice Semi.",
	"NCR",
	"Wafer Scale Integration",
	"IBM",
	"Tristar",
	"Visic",
	"Intl. CMOS Technology",
	"SSSI",
	"MicrochipTechnology",
	"Ricoh Ltd.",
	"VLSI",
	"Micron Technology",
	"SK Hynix",
	"OKI Semiconductor",
	"ACTEL",
	"Sharp",
	"Catalyst",
	"Panasonic",
	"IDT",
	"Cypress",
	"DEC",
	"LSI Logic",
	"Zarlink (former Plessey)",
	"UTMC",
	"Thinking Machine",
	"Thomson CSF",
	"Integrated CMOS (Vertex)",
	"Honeywell",
	"Tektronix",
	"Oracle Corporation",
	"SST",
	"ProMos/Mosel Vitelic",
	"Infineon (former Siemens)",
	"Macronix",
	"Xerox",
	"Plus Logic",
	"SanDisk Corporation",
	"Elan Circuit Tech.",
	"European Silicon Str.",
	"Apple Computer",
	"Xilinx",
	"Compaq",
	"Protocol Engines",
	"SCI",
	"Seiko Instruments",
	"Samsung",
	"I3 Design System",
	"Klic",
	"Crosspoint Solutions",
	"Alliance Semiconductor",
	"Tandem",
	"Hewlett-Packard",
	"Intg. Silicon Solutions",
	"Brooktree",
	"New Media",
	"MHS Electronic",
	"Performance Semi.",
	"Winbond Electronic",
	"Kawasaki Steel",
	"Bright Micro",
	"TECMAR",
	"Exar",
	"PCMCIA",
	"LG Semi (former Goldstar)",
	"Northern Telecom",
	"Sanyo",
	"Array Microsystems",
	"Crystal Semiconductor",
	"Analog Devices",
	"PMC-Sierra",
	"Asparix",
	"Convex Computer",
	"Quality Semiconductor",
	"Nimbus Technology",
	"Transwitch",
	"Micronas (ITT Intermetall)",
	"Cannon",
	"Altera",
	"NEXCOM",
	"QUALCOMM",
	"Sony",
	"Cray Research",
	"AMS(Austria Micro)",
	"Vitesse",
	"Aster Electronics",
	"Bay Networks (Synoptic)",
	"Zentrum or ZMD",
	"TRW",
	"Thesys",
	"Solbourne Computer",
	"Allied-Signal",
	"Dialog",
	"Media Vision",
	"Numonyx Corporation"
};

/*
 * From JEDEC JEP-106AN 1/2014
 * Bank 2 Manufacturers
 */
static const char *manufacturers_bank2[] =
{
	"Cirrus Logic",
	"National Instruments",
	"ILC Data Device",
	"Alcatel Mietec",
	"Micro Linear",
	"Univ. of NC",
	"JTAG Technologies",
	"BAE Systems",
	"Nchip",
	"Galileo Tech",
	"Bestlink Systems",
	"Graychip",
	"GENNUM",
	"VideoLogic",
	"Robert Bosch",
	"Chip Express",
	"DATARAM",
	"United Microelec Corp.",
	"TCSI",
	"Smart Modular",
	"Hughes Aircraft",
	"Lanstar Semiconductor",
	"Qlogic",
	"Kingston",
	"Music Semi",
	"Ericsson Components",
	"SpaSE",
	"Eon Silicon Devices",
	"Programmable Micro Corp",
	"DoD",
	"Integ. Memories Tech.",
	"Corollary Inc.",
	"Dallas Semiconductor",
	"Omnivision",
	"EIV(Switzerland)",
	"Novatel Wireless",
	"Zarlink (former Mitel)",
	"Clearpoint",
	"Cabletron",
	"STEC",
	"Vanguard",
	"Hagiwara Sys-Com",
	"Vantis",
	"Celestica",
	"Century",
	"Hal Computers",
	"Rohm Company Ltd.",
	"Juniper Networks",
	"Libit Signal Processing",
	"Mushkin Enhanced Memory",
	"Tundra Semiconductor",
	"Adaptec Inc.",
	"LightSpeed Semi.",
	"ZSP Corp.",
	"AMIC Technology",
	"Adobe Systems",
	"Dynachip",
	"PNY Electronics",
	"Newport Digital",
	"MMC Networks",
	"T Square",
	"Seiko Epson",
	"Broadcom",
	"Viking Components",
	"V3 Semiconductor",
	"Flextronics (former Orbit)",
	"Suwa Electronics",
	"Transmeta",
	"Micron CMS",
	"American Computer & Digital Components Inc",
	"Enhance 3000 Inc",
	"Tower Semiconductor",
	"CPU Design",
	"Price Point",
	"Maxim Integrated Product",
	"Tellabs",
	"Centaur Technology",
	"Unigen Corporation",
	"Transcend Information",
	"Memory Card Technology",
	"CKD Corporation Ltd.",
	"Capital Instruments, Inc.",
	"Aica Kogyo, Ltd.",
	"Linvex Technology",
	"MSC Vertriebs GmbH",
	"AKM Company, Ltd.",
	"Dynamem, Inc.",
	"NERA ASA",
	"GSI Technology",
	"Dane-Elec (C Memory)",
	"Acorn Computers",
	"Lara Technology",
	"Oak Technology, Inc.",
	"Itec Memory",
	"Tanisys Technology",
	"Truevision",
	"Wintec Industries",
	"Super PC Memory",
	"MGV Memory",
	"Galvantech",
	"Gadzoox Networks",
	"Multi Dimensional Cons.",
	"GateField",
	"Integrated Memory System",
	"Triscend", "XaQti",
	"Goldenram",
	"Clear Logic",
	"Cimaron Communications",
	"Nippon Steel Semi. Corp.",
	"Advantage Memory",
	"AMCC",
	"LeCroy",
	"Yamaha Corporation",
	"Digital Microwave",
	"NetLogic Microsystems",
	"MIMOS Semiconductor",
	"Advanced Fibre",
	"BF Goodrich Data.",
	"Epigram",
	"Acbel Polytech Inc.",
	"Apacer Technology",
	"Admor Memory",
	"FOXCONN",
	"Quadratics Superconductor",
	"3COM",
};

/*
 * From JEDEC JEP-106AN 1/2014
 * Bank 3 Manufacturers
 */
static const char *manufacturers_bank3[] =
{
	"Camintonn Corporation",
	"ISOA Incorporated",
	"Agate Semiconductor",
	"ADMtek Incorporated",
	"HYPERTEC",
	"Adhoc Technologies",
	"MOSAID Technologies",
	"Ardent Technologies",
	"Switchcore",
	"Cisco Systems, Inc.",
	"Allayer Technologies",
	"WorkX AG",
	"Oasis Semiconductor",
	"Novanet Semiconductor",
	"E-M Solutions",
	"Power General",
	"Advanced Hardware Arch.",
	"Inova Semiconductors GmbH",
	"Telocity",
	"Delkin Devices",
	"Symagery Microsystems",
	"C-Port Corporation",
	"SiberCore Technologies",
	"Southland Microsystems",
	"Malleable Technologies",
	"Kendin Communications",
	"Great Technology Microcomputer",
	"Sanmina Corporation",
	"HADCO Corporation",
	"Corsair",
	"Actrans System Inc.",
	"ALPHA Technologies",
	"Silicon Laboratories, Inc. (Cygnal)",
	"Artesyn Technologies",
	"Align Manufacturing",
	"Peregrine Semiconductor",
	"Chameleon Systems",
	"Aplus Flash Technology",
	"MIPS Technologies",
	"Chrysalis ITS",
	"ADTEC Corporation",
	"Kentron Technologies",
	"Win Technologies",
	"Tezzaron Semiconductor",
	"Extreme Packet Devices",
	"RF Micro Devices",
	"Siemens AG",
	"Sarnoff Corporation",
	"Itautec SA",
	"Radiata Inc.",
	"Benchmark Elect. (AVEX)",
	"Legend",
	"SpecTek Incorporated",
	"Hi/fn",
	"Enikia Incorporated",
	"SwitchOn Networks",
	"AANetcom Incorporated",
	"Micro Memory Bank",
	"ESS Technology",
	"Virata Corporation",
	"Excess Bandwidth",
	"West Bay Semiconductor",
	"DSP Group",
	"Newport Communications",
	"Chip2Chip Incorporated",
	"Phobos Corporation",
	"Intellitech Corporation",
	"Nordic VLSI ASA",
	"Ishoni Networks",
	"Silicon Spice",
	"Alchemy Semiconductor",
	"Agilent Technologies",
	"Centillium Communications",
	"W.L. Gore",
	"HanBit Electronics",
	"GlobeSpan",
	"Element 14",
	"Pycon",
	"Saifun Semiconductors",
	"Sibyte, Incorporated",
	"MetaLink Technologies",
	"Feiya Technology",
	"I & C Technology",
	"Shikatronics",
	"Elektrobit",
	"Megic",
	"Com-Tier",
	"Malaysia Micro Solutions",
	"Hyperchip",
	"Gemstone Communications",
	"Anadigm (former Anadyne)",
	"3ParData",
	"Mellanox Technologies",
	"Tenx Technologies",
	"Helix AG",
	"Domosys",
	"Skyup Technology",
	"HiNT Corporation",
	"Chiaro",
	"MDT Technologies GmbH",
	"Exbit Technology A/S",
	"Integrated Technology Express",
	"AVED Memory",
	"Legerity",
	"Jasmine Networks",
	"Caspian Networks",
	"nCUBE",
	"Silicon Access Networks",
	"FDK Corporation",
	"High Bandwidth Access",
	"MultiLink Technology",
	"BRECIS",
	"World Wide Packets",
	"APW",
	"Chicory Systems",
	"Xstream Logic",
	"Fast-Chip",
	"Zucotto Wireless",
	"Realchip",
	"Galaxy Power",
	"eSilicon",
	"Morphics Technology",
	"Accelerant Networks",
	"Silicon Wave",
	"SandCraft",
	"Elpida"
};

/*
 * From JEDEC JEP-106AN 1/2014
 * Bank 4 Manufacturers
 */
static const char *manufacturers_bank4[] =
{
	"Solectron",
	"Optosys Technologies",
	"Buffalo (former Melco)",
	"TriMedia Technologies",
	"Cyan Technologies",
	"Global Locate",
	"Optillion",
	"Terago Communications",
	"Ikanos Communications",
	"Princeton Technology",
	"Nanya Technology",
	"Elite Flash Storage",
	"Mysticom",
	"LightSand Communications",
	"ATI Technologies",
	"Agere Systems",
	"NeoMagic",
	"AuroraNetics",
	"Golden Empire",
	"Mushkin",
	"Tioga Technologies",
	"Netlist",
	"TeraLogic",
	"Cicada Semiconductor",
	"Centon Electronics",
	"Tyco Electronics",
	"Magis Works",
	"Zettacom",
	"Cogency Semiconductor",
	"Chipcon AS",
	"Aspex Technology",
	"F5 Networks",
	"Programmable Silicon Solutions",
	"ChipWrights",
	"Acorn Networks",
	"Quicklogic",
	"Kingmax Semiconductor",
	"BOPS",
	"Flasys",
	"BitBlitz Communications",
	"eMemory Technology",
	"Procket Networks",
	"Purple Ray",
	"Trebia Networks",
	"Delta Electronics",
	"Onex Communications",
	"Ample Communications",
	"Memory Experts Intl",
	"Astute Networks",
	"Azanda Network Devices",
	"Dibcom",
	"Tekmos",
	"API NetWorks",
	"Bay Microsystems",
	"Firecron Ltd",
	"Resonext Communications",
	"Tachys Technologies",
	"Equator Technology",
	"Concept Computer",
	"SILCOM",
	"3Dlabs",
	"c't Magazine",
	"Sanera Systems",
	"Silicon Packets",
	"Viasystems Group",
	"Simtek",
	"Semicon Devices Singapore",
	"Satron Handelsges",
	"Improv Systems",
	"INDUSYS GmbH",
	"Corrent",
	"Infrant Technologies",
	"Ritek Corp",
	"empowerTel Networks",
	"Hypertec",
	"Cavium Networks",
	"PLX Technology",
	"Massana Design",
	"Intrinsity",
	"Valence Semiconductor",
	"Terawave Communications",
	"IceFyre Semiconductor",
	"Primarion",
	"Picochip Designs Ltd",
	"Silverback Systems",
	"Jade Star Technologies",
	"Pijnenburg Securealink",
	"TakeMS International AG",
	"Cambridge Silicon Radio",
	"Swissbit",
	"Nazomi Communications",
	"eWave System",
	"Rockwell Collins",
	"Picocel Co., Ltd.",
	"Alphamosaic Ltd",
	"Sandburst",
	"SiCon Video",
	"NanoAmp Solutions",
	"Ericsson Technology",
	"PrairieComm",
	"Mitac International",
	"Layer N Networks",
	"MtekVision",
	"Allegro Networks",
	"Marvell Semiconductors",
	"Netergy Microelectronic",
	"NVIDIA",
	"Internet Machines",
	"Peak Electronics",
	"Litchfield Communication",
	"Accton Technology",
	"Teradiant Networks",
	"Scaleo Chip",
	"Cortina Systems",
	"RAM Components",
	"Raqia Networks",
	"ClearSpeed",
	"Matsushita Battery",
	"Xelerated",
	"SimpleTech",
	"Utron Technology",
	"Astec International",
	"AVM gmbH",
	"Redux Communications",
	"Dot Hill Systems",
	"TeraChip"
};

/*
 * From JEDEC JEP-106AN 1/2014
 * Bank 5 Manufacturers
 */
static const char *manufacturers_bank5[] =
{
	"T-RAM Incorporated",
	"Innovics Wireless",
	"Teknovus",
	"KeyEye Communications",
	"Runcom Technologies",
	"RedSwitch",
	"Dotcast",
	"Silicon Mountain Memory",
	"Signia Technologies",
	"Pixim",
	"Galazar Networks",
	"White Electronic Designs",
	"Patriot Scientific",
	"Neoaxiom Corporation",
	"3Y Power Technology",
	"Scaleo Chip",
	"Potentia Power Systems",
	"C-guys Incorporated",
	"Digital Communications Technology Incorporated",
	"Silicon-Based Technology",
	"Fulcrum Microsystems",
	"Positivo Informatica Ltd",
	"XIOtech Corporation",
	"PortalPlayer",
	"Zhiying Software",
	"ParkerVision, Inc",
	"Phonex Broadband",
	"Skyworks Solutions",
	"Entropic Communications",
	"I'M Intelligent Memory Ltd.",
	"Zensys A/S",
	"Legend Silicon Corp.",
	"sci-worx GmbH",
	"SMSC (Standard Microsystems)",
	"Renesas Technology",
	"Raza Microelectronics",
	"Phyworks",
	"MediaTek",
	"Non-cents Productions",
	"US Modular",
	"Wintegra Ltd",
	"Mathstar",
	"StarCore",
	"Oplus Technologies",
	"Mindspeed",
	"Just Young Computer",
	"Radia Communications",
	"OCZ",
	"Emuzed",
	"LOGIC Devices",
	"Inphi Corporation",
	"Quake Technologies",
	"Vixel",
	"SolusTek",
	"Kongsberg Maritime",
	"Faraday Technology",
	"Altium Ltd.",
	"Insyte",
	"ARM Ltd.",
	"DigiVision",
	"Vativ Technologies",
	"Endicott Interconnect Technologies",
	"Pericom",
	"Bandspeed",
	"LeWiz Communications",
	"CPU Technology",
	"Ramaxel Technology",
	"DSP Group",
	"Axis Communications",
	"Legacy Electronics",
	"Chrontel",
	"Powerchip Semiconductor",
	"MobilEye Technologies",
	"Excel Semiconductor",
	"A-DATA Technology",
	"VirtualDigm",
	"G Skill Intl",
	"Quanta Computer",
	"Yield Microelectronics",
	"Afa Technologies",
	"KINGBOX Technology Co. Ltd.",
	"Ceva",
	"iStor Networks",
	"Advance Modules",
	"Microsoft",
	"Open-Silicon",
	"Goal Semiconductor",
	"ARC International",
	"Simmtec",
	"Metanoia",
	"Key Stream",
	"Lowrance Electronics",
	"Adimos",
	"SiGe Semiconductor",
	"Fodus Communications",
	"Credence Systems Corp.",
	"Genesis Microchip Inc.",
	"Vihana, Inc.",
	"WIS Technologies",
	"GateChange Technologies",
	"High Density Devices AS",
	"Synopsys",
	"Gigaram",
	"Enigma Semiconductor Inc.",
	"Century Micro Inc.",
	"Icera Semiconductor",
	"Mediaworks Integrated Systems",
	"O'Neil Product Development",
	"Supreme Top Technology Ltd.",
	"MicroDisplay Corporation",
	"Team Group Inc.",
	"Sinett Corporation",
	"Toshiba Corporation",
	"Tensilica",
	"SiRF Technology",
	"Bacoc Inc.",
	"SMaL Camera Technologies",
	"Thomson SC",
	"Airgo Networks",
	"Wisair Ltd.",
	"SigmaTel",
	"Arkados",
	"Compete IT gmbH Co. KG",
	"Eudar Technology Inc.",
	"Focus Enhancements",
	"Xyratex"
};

/*
 * From JEDEC JEP-106AN 1/2014
 * Bank 6 Manufacturers
 */
static const char *manufacturers_bank6[] =
{
	"Specular Networks",
	"Patriot Memory",
	"U-Chip Technology Corp.",
	"Silicon Optix",
	"Greenfield Networks",
	"CompuRAM GmbH",
	"Stargen, Inc.",
	"NetCell Corporation",
	"Excalibrus Technologies Ltd",
	"SCM Microsystems",
	"Xsigo Systems, Inc.",
	"CHIPS & Systems Inc",
	"Tier 1 Multichip Solutions",
	"CWRL Labs",
	"Teradici",
	"Gigaram, Inc.",
	"g2 Microsystems",
	"PowerFlash Semiconductor",
	"P.A. Semi, Inc.",
	"NovaTech Solutions, S.A.",
	"c2 Microsystems, Inc.",
	"Level5 Networks",
	"COS Memory AG",
	"Innovasic Semiconductor",
	"02IC Co. Ltd", "Tabula, Inc.",
	"Crucial Technology",
	"Chelsio Communications",
	"Solarflare Communications",
	"Xambala Inc.",
	"EADS Astrium",
	"Terra Semiconductor, Inc",
	"Imaging Works, Inc.",
	"Astute Networks, Inc.",
	"Tzero",
	"Emulex",
	"Power-One",
	"Pulse~LINK Inc.",
	"Hon Hai Precision Industry",
	"White Rock Networks Inc.",
	"Telegent Systems USA, Inc.",
	"Atrua Technologies, Inc.",
	"Acbel Polytech Inc.",
	"eRide Inc.",
	"ULi Electronics Inc.",
	"Magnum Semiconductor Inc.",
	"neoOne Technology, Inc.",
	"Connex Technology, Inc.",
	"Stream Processors, Inc.",
	"Focus Enhancements",
	"Telecis Wireless, Inc.",
	"uNav Microelectronics",
	"Tarari, Inc.",
	"Ambric, Inc.",
	"Newport Media, Inc.",
	"VMTS",
	"Enuclia Semiconductor, Inc.",
	"Virtium Technology Inc.",
	"Solid State System Co., Ltd.",
	"Kian Tech LLC",
	"Artimi",
	"Power Quotient International",
	"Avago Technologies",
	"ADTechnology",
	"Sigma Designs",
	"SiCortex, Inc.",
	"Ventura Technology Group",
	"eASIC",
	"M.H.S. SAS",
	"Micro Star International",
	"Rapport Inc.",
	"Makway International",
	"Broad Reach Engineering Co.",
	"Semiconductor Mfg Intl Corp",
	"SiConnect",
	"FCI USA Inc.",
	"Validity Sensors",
	"Coney Technology Co. Ltd.",
	"Spans Logic",
	"Neterion Inc.",
	"Qimonda",
	"New Japan Radio Co. Ltd.",
	"Velogix",
	"Montalvo Systems",
	"iVivity Inc.",
	"Walton Chaintech",
	"AENEON",
	"Lorom Industrial Co. Ltd.",
	"Radiospire Networks",
	"Sensio Technologies, Inc.",
	"Nethra Imaging",
	"Hexon Technology Pte Ltd",
	"CompuStocx (CSX)",
	"Methode Electronics, Inc.",
	"Connect One Ltd.",
	"Opulan Technologies",
	"Septentrio NV",
	"Goldenmars Technology Inc.",
	"Kreton Corporation",
	"Cochlear Ltd.",
	"Altair Semiconductor",
	"NetEffect, Inc.",
	"Spansion, Inc.",
	"Taiwan Semiconductor Mfg",
	"Emphany Systems Inc.",
	"ApaceWave Technologies",
	"Mobilygen Corporation",
	"Tego",
	"Cswitch Corporation",
	"Haier (Beijing) IC Design Co.",
	"MetaRAM",
	"Axel Electronics Co. Ltd.",
	"Tilera Corporation",
	"Aquantia",
	"Vivace Semiconductor",
	"Redpine Signals",
	"Octalica",
	"InterDigital Communications",
	"Avant Technology",
	"Asrock, Inc.",
	"Availink",
	"Quartics, Inc.",
	"Element CXI",
	"Innovaciones Microelectronicas",
	"VeriSilicon Microelectronics",
	"W5 Networks"
};

/*
 * From JEDEC JEP-106AN 1/2014
 * Bank 7 Manufacturers
 */
static const char *manufacturers_bank7[] =
{
	"MOVEKING",
	"Mavrix Technology, Inc.",
	"CellGuide Ltd.",
	"Faraday Technology",
	"Diablo Technologies, Inc.",
	"Jennic",
	"Octasic",
	"Molex Incorporated",
	"3Leaf Networks",
	"Bright Micron Technology",
	"Netxen",
	"NextWave Broadband Inc.",
	"DisplayLink",
	"ZMOS Technology",
	"Tec-Hill",
	"Multigig, Inc.",
	"Amimon",
	"Euphonic Technologies, Inc.",
	"BRN Phoenix",
	"InSilica",
	"Ember Corporation",
	"Avexir Technologies Corporation",
	"Echelon Corporation",
	"Edgewater Computer Systems",
	"XMOS Semiconductor Ltd.",
	"GENUSION, Inc.",
	"Memory Corp NV",
	"SiliconBlue Technologies",
	"Rambus Inc.",
	"Andes Technology Corporation",
	"Coronis Systems",
	"Achronix Semiconductor",
	"Siano Mobile Silicon Ltd.",
	"Semtech Corporation",
	"Pixelworks Inc.",
	"Gaisler Research AB",
	"Teranetics",
	"Toppan Printing Co. Ltd.",
	"Kingxcon",
	"Silicon Integrated Systems",
	"I-O Data Device, Inc.",
	"NDS Americas Inc.",
	"Solomon Systech Limited",
	"On Demand Microelectronics",
	"Amicus Wireless Inc.",
	"SMARDTV SNC",
	"Comsys Communication Ltd.",
	"Movidia Ltd.",
	"Javad GNSS, Inc.",
	"Montage Technology Group",
	"Trident Microsystems",
	"Super Talent",
	"Optichron, Inc.",
	"Future Waves UK Ltd.",
	"SiBEAM, Inc.",
	"Inicore,Inc.",
	"Virident Systems",
	"M2000, Inc.",
	"ZeroG Wireless, Inc.",
	"Gingle Technology Co. Ltd.",
	"Space Micro Inc.",
	"Wilocity",
	"Novafora, Inc.",
	"iKoa Corporation",
	"ASint Technology",
	"Ramtron",
	"Plato Networks Inc.",
	"IPtronics AS",
	"Infinite-Memories",
	"Parade Technologies Inc.",
	"Dune Networks",
	"GigaDevice Semiconductor",
	"Modu Ltd.",
	"CEITEC",
	"Northrop Grumman",
	"XRONET Corporation",
	"Sicon Semiconductor AB",
	"Atla Electronics Co. Ltd.",
	"TOPRAM Technology",
	"Silego Technology Inc.",
	"Kinglife",
	"Ability Industries Ltd.",
	"Silicon Power Computer &	Communications",
	"Augusta Technology, Inc.",
	"Nantronics Semiconductors",
	"Hilscher Gesellschaft",
	"Quixant Ltd.",
	"Percello Ltd.",
	"NextIO Inc.",
	"Scanimetrics Inc.",
	"FS-Semi Company Ltd.",
	"Infinera Corporation",
	"SandForce Inc.",
	"Lexar Media",
	"Teradyne Inc.",
	"Memory Exchange Corp.",
	"Suzhou Smartek Electronics",
	"Avantium Corporation",
	"ATP Electronics Inc.",
	"Valens Semiconductor Ltd",
	"Agate Logic, Inc.",
	"Netronome",
	"Zenverge, Inc.",
	"N-trig Ltd",
	"SanMax Technologies Inc.",
	"Contour Semiconductor Inc.",
	"TwinMOS",
	"Silicon Systems, Inc.",
	"V-Color Technology Inc.",
	"Certicom Corporation",
	"JSC ICC Milandr",
	"PhotoFast Global Inc.",
	"InnoDisk Corporation",
	"Muscle Power",
	"Energy Micro",
	"Innofidei",
	"CopperGate Communications",
	"Holtek Semiconductor Inc.",
	"Myson Century, Inc.",
	"FIDELIX",
	"Red Digital Cinema",
	"Densbits Technology",
	"Zempro",
	"MoSys",
	"Provigent",
	"Triad Semiconductor, Inc."
};

/*
 * From JEDEC JEP-106AN 1/2014
 * Bank 8 Manufacturers
 */
static const char *manufacturers_bank8[] =
{
	"Siklu Communication Ltd.",
	"A Force Manufacturing Ltd.",
	"Strontium",
	"Abilis Systems",
	"Siglead, Inc.",
	"Ubicom, Inc.",
	"Unifosa Corporation",
	"Stretch, Inc.",
	"Lantiq Deutschland GmbH",
	"Visipro.",
	"EKMemory",
	"Microelectronics Institute ZTE",
	"Cognovo Ltd.",
	"Carry Technology Co. Ltd.",
	"Nokia",
	"King Tiger Technology",
	"Sierra Wireless",
	"HT Micron",
	"Albatron Technology Co. Ltd.",
	"Leica Geosystems AG",
	"BroadLight",
	"AEXEA",
	"ClariPhy Communications, Inc.",
	"Green Plug",
	"Design Art Networks",
	"Mach Xtreme Technology Ltd.",
	"ATO Solutions Co. Ltd.",
	"Ramsta",
	"Greenliant Systems, Ltd.",
	"Teikon",
	"Antec Hadron",
	"NavCom Technology, Inc.",
	"Shanghai Fudan Microelectronics",
	"Calxeda, Inc.",
	"JSC EDC Electronics",
	"Kandit Technology Co. Ltd.",
	"Ramos Technology",
	"Goldenmars Technology",
	"XeL Technology Inc.",
	"Newzone Corporation",
	"ShenZhen MercyPower Tech",
	"Nanjing Yihuo Technology",
	"Nethra Imaging Inc.",
	"SiTel Semiconductor BV",
	"SolidGear Corporation",
	"Topower Computer Ind Co Ltd.",
	"Wilocity",
	"Profichip GmbH",
	"Gerad Technologies",
	"Ritek Corporation",
	"Gomos Technology Limited",
	"Memoright Corporation",
	"D-Broad, Inc.",
	"HiSilicon Technologies",
	"Syndiant Inc..",
	"Enverv Inc.",
	"Cognex",
	"Xinnova Technology Inc.",
	"Ultron AG",
	"Concord Idea Corporation",
	"AIM Corporation",
	"Lifetime Memory Products",
	"Ramsway",
	"Recore Systems B.V.",
	"Haotian Jinshibo Science Tech",
	"Being Advanced Memory",
	"Adesto Technologies",
	"Giantec Semiconductor, Inc.",
	"HMD Electronics AG",
	"Gloway International (HK)",
	"Kingcore",
	"Anucell Technology Holding",
	"Accord Software & Systems Pvt. Ltd.",
	"Active-Semi Inc.",
	"Denso Corporation",
	"TLSI Inc.",
	"Qidan",
	"Mustang",
	"Orca Systems",
	"Passif Semiconductor",
	"GigaDevice Semiconductor (Beijing) Inc.",
	"Memphis Electronic",
	"Beckhoff Automation GmbH",
	"Harmony Semiconductor Corp",
	"Air Computers SRL",
	"TMT Memory",
	"Eorex Corporation",
	"Xingtera",
	"Netsol",
	"Bestdon Technology Co. Ltd.",
	"Baysand Inc.",
	"Uroad Technology Co. Ltd.",
	"Wilk Elektronik S.A.",
	"AAI",
	"Harman",
	"Berg Microelectronics Inc.",
	"ASSIA, Inc.",
	"Visiontek Products LLC",
	"OCMEMORY",
	"Welink Solution Inc.",
	"Shark Gaming",
	"Avalanche Technology",
	"R&D Center ELVEES OJSC",
	"KingboMars Technology Co. Ltd.",
	"High Bridge Solutions Industria Eletronica",
	"Transcend Technology Co. Ltd.",
	"Everspin Technologies",
	"Hon-Hai Precision",
	"Smart Storage Systems",
	"Toumaz Group",
	"Zentel Electronics Corporation",
	"Panram International Corporation",
	"Silicon Space Technology",
	"LITE-ON IT Corporation",
	"Inuitive",
	"HMicro",
	"BittWare, Inc.",
	"GLOBALFOUNDRIES",
	"ACPI Digital Co. Ltd.",
	"Annapurna Labs",
	"AcSiP Technology Corporation",
	"Idea! Electronic Systems",
	"Gowe Technology Co. Ltd.",
	"Hermes Testing Solutions, Inc.",
	"Positivo BGH",
	"Intelligence Silicon Technology"
};

/*
 * From JEDEC JEP-106AN 1/2014
 * Bank 9 Manufacturers
 */
static const char *manufacturers_bank9[] =
{
	"3D PLUS",
	"Diehl Aerospace",
	"Fairchild",
	"Mercury Systems",
	"Sonics, Inc.",
	"GE Intelligent Platforms GmbH & Co.",
	"Shenzhen Jinge Information Co. Ltd.",
	"SCWW",
	"Silicon Motion Inc.",
	"Anurag",
	"King Kong",
	"FROM30 Co. Ltd.",
	"Gowin Semiconductor Corp",
	"Fremont Micro Devices Ltd.",
	"Ericsson Modems",
	"Exelis",
	"Satixfy Ltd.",
	"Galaxy Microsystems Ltd.",
	"Gloway International Co. Ltd.",
	"Lab",
	"Smart Energy Instruments",
	"Approved Memory Corporation",
	"Axell Corporation",
	"ISD Technology Limited",
	"Phytium",
	"Xi�an SinoChip Semiconductor",
	"Ambiq Micro",
	"eveRAM Technology, Inc.",
	"Infomax",
	"Butterfly Network, Inc.",
	"Shenzhen City Gcai Electronics",
	"Stack Devices Corporation",
	"ADK Media Group",
	"TSP Global Co., Ltd.",
	"HighX",
	"Shenzhen Elicks Technology",
	"ISSI/Chingis",
	"Google, Inc.",
	"Dasima International Development",
	"Leahkinn Technology Limited"
};

static const char **manufacturers[MAX_MANUFACTURER_BANKS] = {
	manufacturers_bank1,
	manufacturers_bank2,
	manufacturers_bank3,
	manufacturers_bank4,
	manufacturers_bank5,
	manufacturers_bank6,
	manufacturers_bank7,
	manufacturers_bank8,
	manufacturers_bank9
};


static int parity(int value)
{
	value ^= value >> 16;
	value ^= value >> 8;
	value ^= value >> 4;
	value &= 0xf;

	return (0x6996 >> value) & 1;
}

/*!
 * Lookup the manufacturer name given the manufacturer ID.
 */
int lookup_jedec_jep106_manufacturer(
		const unsigned char *manufacturer_id, const int manufacturer_id_len,
		char *manufacturer, const COMMON_SIZE manufacturer_len)
{
	int rc = COMMON_ERR_INVALIDPARAMETER;

	if (manufacturer_id && manufacturer_id_len > 1 &&
		manufacturer_id_len <= MAX_MANUFACTURER_BANKS &&
		manufacturer && manufacturer_len > 0)
	{
		unsigned char id = 0;
		int index = 0;
		int byte = manufacturer_id_len;

		// find the correct bank
		do
		{
			index++;
		}
		while ((--byte && (*manufacturer_id++ == 0x7f)));
		id = *--manufacturer_id;

		if (parity(id) == 1)
		{
			s_strcpy(manufacturer, (char *)manufacturers[index - 1][(id & 0x7f) - 1],
					manufacturer_len);
			rc = COMMON_SUCCESS;
		}

		if (rc != COMMON_SUCCESS)
		{
			s_strcpy(manufacturer, "Undefined", manufacturer_len);
		}
	}

	return rc;
}
