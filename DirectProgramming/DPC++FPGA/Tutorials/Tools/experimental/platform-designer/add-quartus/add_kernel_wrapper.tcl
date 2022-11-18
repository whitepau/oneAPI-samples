package require -exact qsys 21.3

# create the system "add_kernel_wrapper"
proc do_create_add_kernel_wrapper {} {
	# create the system
	create_system add_kernel_wrapper
	set_project_property DEVICE {10AS066N3F40E2SG}
	set_project_property DEVICE_FAMILY {Arria 10}
	set_project_property HIDE_FROM_IP_CATALOG {false}
	set_use_testbench_naming_pattern 0 {}

	# add HDL parameters

	# add the components
	add_component add_fpga_ip_export_1_di_0 ip/add_kernel_wrapper/add_kernel_wrapper_add_fpga_ip_export_1_di_0.ip add_fpga_ip_export_1_di add_fpga_ip_export_1_di_0 1.0
	load_component add_fpga_ip_export_1_di_0
	set_component_project_property HIDE_FROM_IP_CATALOG {false}
	save_component
	load_instantiation add_fpga_ip_export_1_di_0
	remove_instantiation_interfaces_and_ports
	add_instantiation_interface clock clock INPUT
	set_instantiation_interface_parameter_value clock clockRate {0}
	set_instantiation_interface_parameter_value clock externallyDriven {false}
	set_instantiation_interface_parameter_value clock ptfSchematicName {}
	add_instantiation_interface_port clock clock clk 1 STD_LOGIC Input
	add_instantiation_interface clock2x clock INPUT
	set_instantiation_interface_parameter_value clock2x clockRate {0}
	set_instantiation_interface_parameter_value clock2x externallyDriven {false}
	set_instantiation_interface_parameter_value clock2x ptfSchematicName {}
	add_instantiation_interface_port clock2x clock2x clk 1 STD_LOGIC Input
	add_instantiation_interface resetn reset INPUT
	set_instantiation_interface_parameter_value resetn associatedClock {clock}
	set_instantiation_interface_parameter_value resetn synchronousEdges {BOTH}
	add_instantiation_interface_port resetn resetn reset_n 1 STD_LOGIC Input
	add_instantiation_interface device_exception_bus conduit INPUT
	set_instantiation_interface_parameter_value device_exception_bus associatedClock {clock}
	set_instantiation_interface_parameter_value device_exception_bus associatedReset {resetn}
	set_instantiation_interface_parameter_value device_exception_bus prSafe {false}
	add_instantiation_interface_port device_exception_bus device_exception_bus data 64 STD_LOGIC_VECTOR Output
	add_instantiation_interface kernel_irqs interrupt INPUT
	set_instantiation_interface_parameter_value kernel_irqs associatedAddressablePoint {}
	set_instantiation_interface_parameter_value kernel_irqs associatedClock {clock}
	set_instantiation_interface_parameter_value kernel_irqs associatedReset {resetn}
	set_instantiation_interface_parameter_value kernel_irqs bridgedReceiverOffset {0}
	set_instantiation_interface_parameter_value kernel_irqs bridgesToReceiver {}
	set_instantiation_interface_parameter_value kernel_irqs irqScheme {NONE}
	add_instantiation_interface_port kernel_irqs kernel_irqs irq 1 STD_LOGIC Output
	add_instantiation_interface csr_ring_root_avs avalon INPUT
	set_instantiation_interface_parameter_value csr_ring_root_avs addressAlignment {DYNAMIC}
	set_instantiation_interface_parameter_value csr_ring_root_avs addressGroup {0}
	set_instantiation_interface_parameter_value csr_ring_root_avs addressSpan {256}
	set_instantiation_interface_parameter_value csr_ring_root_avs addressUnits {WORDS}
	set_instantiation_interface_parameter_value csr_ring_root_avs alwaysBurstMaxBurst {false}
	set_instantiation_interface_parameter_value csr_ring_root_avs associatedClock {clock}
	set_instantiation_interface_parameter_value csr_ring_root_avs associatedReset {resetn}
	set_instantiation_interface_parameter_value csr_ring_root_avs bitsPerSymbol {8}
	set_instantiation_interface_parameter_value csr_ring_root_avs bridgedAddressOffset {0}
	set_instantiation_interface_parameter_value csr_ring_root_avs bridgesToMaster {}
	set_instantiation_interface_parameter_value csr_ring_root_avs burstOnBurstBoundariesOnly {false}
	set_instantiation_interface_parameter_value csr_ring_root_avs burstcountUnits {WORDS}
	set_instantiation_interface_parameter_value csr_ring_root_avs constantBurstBehavior {false}
	set_instantiation_interface_parameter_value csr_ring_root_avs explicitAddressSpan {0}
	set_instantiation_interface_parameter_value csr_ring_root_avs holdTime {0}
	set_instantiation_interface_parameter_value csr_ring_root_avs interleaveBursts {false}
	set_instantiation_interface_parameter_value csr_ring_root_avs isBigEndian {false}
	set_instantiation_interface_parameter_value csr_ring_root_avs isFlash {false}
	set_instantiation_interface_parameter_value csr_ring_root_avs isMemoryDevice {false}
	set_instantiation_interface_parameter_value csr_ring_root_avs isNonVolatileStorage {false}
	set_instantiation_interface_parameter_value csr_ring_root_avs linewrapBursts {false}
	set_instantiation_interface_parameter_value csr_ring_root_avs maximumPendingReadTransactions {1}
	set_instantiation_interface_parameter_value csr_ring_root_avs maximumPendingWriteTransactions {0}
	set_instantiation_interface_parameter_value csr_ring_root_avs minimumReadLatency {1}
	set_instantiation_interface_parameter_value csr_ring_root_avs minimumResponseLatency {1}
	set_instantiation_interface_parameter_value csr_ring_root_avs minimumUninterruptedRunLength {1}
	set_instantiation_interface_parameter_value csr_ring_root_avs prSafe {false}
	set_instantiation_interface_parameter_value csr_ring_root_avs printableDevice {false}
	set_instantiation_interface_parameter_value csr_ring_root_avs readLatency {0}
	set_instantiation_interface_parameter_value csr_ring_root_avs readWaitStates {0}
	set_instantiation_interface_parameter_value csr_ring_root_avs readWaitTime {0}
	set_instantiation_interface_parameter_value csr_ring_root_avs registerIncomingSignals {false}
	set_instantiation_interface_parameter_value csr_ring_root_avs registerOutgoingSignals {false}
	set_instantiation_interface_parameter_value csr_ring_root_avs setupTime {0}
	set_instantiation_interface_parameter_value csr_ring_root_avs timingUnits {Cycles}
	set_instantiation_interface_parameter_value csr_ring_root_avs transparentBridge {false}
	set_instantiation_interface_parameter_value csr_ring_root_avs waitrequestAllowance {0}
	set_instantiation_interface_parameter_value csr_ring_root_avs wellBehavedWaitrequest {false}
	set_instantiation_interface_parameter_value csr_ring_root_avs writeLatency {0}
	set_instantiation_interface_parameter_value csr_ring_root_avs writeWaitStates {0}
	set_instantiation_interface_parameter_value csr_ring_root_avs writeWaitTime {0}
	set_instantiation_interface_assignment_value csr_ring_root_avs embeddedsw.configuration.isFlash {0}
	set_instantiation_interface_assignment_value csr_ring_root_avs embeddedsw.configuration.isMemoryDevice {0}
	set_instantiation_interface_assignment_value csr_ring_root_avs embeddedsw.configuration.isNonVolatileStorage {0}
	set_instantiation_interface_assignment_value csr_ring_root_avs embeddedsw.configuration.isPrintableDevice {0}
	set_instantiation_interface_assignment_value csr_ring_root_avs hls.cosim.name {}
	set_instantiation_interface_sysinfo_parameter_value csr_ring_root_avs address_map {<address-map><slave name='csr_ring_root_avs' start='0x0' end='0x100' datawidth='64' /></address-map>}
	set_instantiation_interface_sysinfo_parameter_value csr_ring_root_avs address_width {8}
	set_instantiation_interface_sysinfo_parameter_value csr_ring_root_avs max_slave_data_width {64}
	add_instantiation_interface_port csr_ring_root_avs csr_ring_root_avs_read read 1 STD_LOGIC Input
	add_instantiation_interface_port csr_ring_root_avs csr_ring_root_avs_readdata readdata 64 STD_LOGIC_VECTOR Output
	add_instantiation_interface_port csr_ring_root_avs csr_ring_root_avs_readdatavalid readdatavalid 1 STD_LOGIC Output
	add_instantiation_interface_port csr_ring_root_avs csr_ring_root_avs_write write 1 STD_LOGIC Input
	add_instantiation_interface_port csr_ring_root_avs csr_ring_root_avs_writedata writedata 64 STD_LOGIC_VECTOR Input
	add_instantiation_interface_port csr_ring_root_avs csr_ring_root_avs_address address 5 STD_LOGIC_VECTOR Input
	add_instantiation_interface_port csr_ring_root_avs csr_ring_root_avs_byteenable byteenable 8 STD_LOGIC_VECTOR Input
	add_instantiation_interface_port csr_ring_root_avs csr_ring_root_avs_waitrequest waitrequest 1 STD_LOGIC Output
	save_instantiation
	add_component clock_in ip/add_kernel_wrapper/add_kernel_wrapper_clock_in.ip altera_clock_bridge clock_in 19.2.0
	load_component clock_in
	set_component_parameter_value EXPLICIT_CLOCK_RATE {50000000.0}
	set_component_parameter_value NUM_CLOCK_OUTPUTS {1}
	set_component_project_property HIDE_FROM_IP_CATALOG {false}
	save_component
	load_instantiation clock_in
	remove_instantiation_interfaces_and_ports
	add_instantiation_interface in_clk clock INPUT
	set_instantiation_interface_parameter_value in_clk clockRate {0}
	set_instantiation_interface_parameter_value in_clk externallyDriven {false}
	set_instantiation_interface_parameter_value in_clk ptfSchematicName {}
	add_instantiation_interface_port in_clk in_clk clk 1 STD_LOGIC Input
	add_instantiation_interface out_clk clock OUTPUT
	set_instantiation_interface_parameter_value out_clk associatedDirectClock {in_clk}
	set_instantiation_interface_parameter_value out_clk clockRate {50000000}
	set_instantiation_interface_parameter_value out_clk clockRateKnown {true}
	set_instantiation_interface_parameter_value out_clk externallyDriven {false}
	set_instantiation_interface_parameter_value out_clk ptfSchematicName {}
	set_instantiation_interface_sysinfo_parameter_value out_clk clock_rate {50000000}
	add_instantiation_interface_port out_clk out_clk clk 1 STD_LOGIC Output
	save_instantiation
	add_component master_0 ip/add_kernel_wrapper/add_kernel_wrapper_master_0.ip altera_jtag_avalon_master master_0 19.1
	load_component master_0
	set_component_parameter_value FAST_VER {0}
	set_component_parameter_value FIFO_DEPTHS {2}
	set_component_parameter_value PLI_PORT {50000}
	set_component_parameter_value USE_PLI {0}
	set_component_project_property HIDE_FROM_IP_CATALOG {false}
	save_component
	load_instantiation master_0
	remove_instantiation_interfaces_and_ports
	set_instantiation_assignment_value debug.hostConnection {type jtag id 110:132}
	add_instantiation_interface clk clock INPUT
	set_instantiation_interface_parameter_value clk clockRate {0}
	set_instantiation_interface_parameter_value clk externallyDriven {false}
	set_instantiation_interface_parameter_value clk ptfSchematicName {}
	add_instantiation_interface_port clk clk_clk clk 1 STD_LOGIC Input
	add_instantiation_interface clk_reset reset INPUT
	set_instantiation_interface_parameter_value clk_reset associatedClock {}
	set_instantiation_interface_parameter_value clk_reset synchronousEdges {NONE}
	add_instantiation_interface_port clk_reset clk_reset_reset reset 1 STD_LOGIC Input
	add_instantiation_interface master_reset reset OUTPUT
	set_instantiation_interface_parameter_value master_reset associatedClock {}
	set_instantiation_interface_parameter_value master_reset associatedDirectReset {}
	set_instantiation_interface_parameter_value master_reset associatedResetSinks {none}
	set_instantiation_interface_parameter_value master_reset synchronousEdges {NONE}
	add_instantiation_interface_port master_reset master_reset_reset reset 1 STD_LOGIC Output
	add_instantiation_interface master avalon OUTPUT
	set_instantiation_interface_parameter_value master adaptsTo {}
	set_instantiation_interface_parameter_value master addressGroup {0}
	set_instantiation_interface_parameter_value master addressUnits {SYMBOLS}
	set_instantiation_interface_parameter_value master alwaysBurstMaxBurst {false}
	set_instantiation_interface_parameter_value master associatedClock {clk}
	set_instantiation_interface_parameter_value master associatedReset {clk_reset}
	set_instantiation_interface_parameter_value master bitsPerSymbol {8}
	set_instantiation_interface_parameter_value master burstOnBurstBoundariesOnly {false}
	set_instantiation_interface_parameter_value master burstcountUnits {WORDS}
	set_instantiation_interface_parameter_value master constantBurstBehavior {false}
	set_instantiation_interface_parameter_value master dBSBigEndian {false}
	set_instantiation_interface_parameter_value master doStreamReads {false}
	set_instantiation_interface_parameter_value master doStreamWrites {false}
	set_instantiation_interface_parameter_value master holdTime {0}
	set_instantiation_interface_parameter_value master interleaveBursts {false}
	set_instantiation_interface_parameter_value master isAsynchronous {false}
	set_instantiation_interface_parameter_value master isBigEndian {false}
	set_instantiation_interface_parameter_value master isReadable {false}
	set_instantiation_interface_parameter_value master isWriteable {false}
	set_instantiation_interface_parameter_value master linewrapBursts {false}
	set_instantiation_interface_parameter_value master maxAddressWidth {32}
	set_instantiation_interface_parameter_value master maximumPendingReadTransactions {0}
	set_instantiation_interface_parameter_value master maximumPendingWriteTransactions {0}
	set_instantiation_interface_parameter_value master minimumReadLatency {1}
	set_instantiation_interface_parameter_value master minimumResponseLatency {1}
	set_instantiation_interface_parameter_value master prSafe {false}
	set_instantiation_interface_parameter_value master readLatency {0}
	set_instantiation_interface_parameter_value master readWaitTime {1}
	set_instantiation_interface_parameter_value master registerIncomingSignals {false}
	set_instantiation_interface_parameter_value master registerOutgoingSignals {false}
	set_instantiation_interface_parameter_value master setupTime {0}
	set_instantiation_interface_parameter_value master timingUnits {Cycles}
	set_instantiation_interface_parameter_value master waitrequestAllowance {0}
	set_instantiation_interface_parameter_value master writeWaitTime {0}
	set_instantiation_interface_assignment_value master debug.controlledBy {in_stream}
	set_instantiation_interface_assignment_value master debug.providesServices {master}
	set_instantiation_interface_assignment_value master debug.typeName {altera_jtag_avalon_master.master}
	set_instantiation_interface_assignment_value master debug.visible {true}
	add_instantiation_interface_port master master_address address 32 STD_LOGIC_VECTOR Output
	add_instantiation_interface_port master master_readdata readdata 32 STD_LOGIC_VECTOR Input
	add_instantiation_interface_port master master_read read 1 STD_LOGIC Output
	add_instantiation_interface_port master master_write write 1 STD_LOGIC Output
	add_instantiation_interface_port master master_writedata writedata 32 STD_LOGIC_VECTOR Output
	add_instantiation_interface_port master master_waitrequest waitrequest 1 STD_LOGIC Input
	add_instantiation_interface_port master master_readdatavalid readdatavalid 1 STD_LOGIC Input
	add_instantiation_interface_port master master_byteenable byteenable 4 STD_LOGIC_VECTOR Output
	save_instantiation
	add_component reset_in ip/add_kernel_wrapper/add_kernel_wrapper_reset_in.ip altera_reset_bridge reset_in 19.2.0
	load_component reset_in
	set_component_parameter_value ACTIVE_LOW_RESET {0}
	set_component_parameter_value NUM_RESET_OUTPUTS {1}
	set_component_parameter_value SYNCHRONOUS_EDGES {deassert}
	set_component_parameter_value SYNC_RESET {0}
	set_component_parameter_value USE_RESET_REQUEST {0}
	set_component_project_property HIDE_FROM_IP_CATALOG {false}
	save_component
	load_instantiation reset_in
	remove_instantiation_interfaces_and_ports
	add_instantiation_interface clk clock INPUT
	set_instantiation_interface_parameter_value clk clockRate {0}
	set_instantiation_interface_parameter_value clk externallyDriven {false}
	set_instantiation_interface_parameter_value clk ptfSchematicName {}
	add_instantiation_interface_port clk clk clk 1 STD_LOGIC Input
	add_instantiation_interface in_reset reset INPUT
	set_instantiation_interface_parameter_value in_reset associatedClock {clk}
	set_instantiation_interface_parameter_value in_reset synchronousEdges {DEASSERT}
	add_instantiation_interface_port in_reset in_reset reset 1 STD_LOGIC Input
	add_instantiation_interface out_reset reset OUTPUT
	set_instantiation_interface_parameter_value out_reset associatedClock {clk}
	set_instantiation_interface_parameter_value out_reset associatedDirectReset {in_reset}
	set_instantiation_interface_parameter_value out_reset associatedResetSinks {in_reset}
	set_instantiation_interface_parameter_value out_reset synchronousEdges {DEASSERT}
	add_instantiation_interface_port out_reset out_reset reset 1 STD_LOGIC Output
	save_instantiation

	# add wirelevel expressions

	# preserve ports for debug

	# add the connections
	add_connection clock_in.out_clk/add_fpga_ip_export_1_di_0.clock
	set_connection_parameter_value clock_in.out_clk/add_fpga_ip_export_1_di_0.clock clockDomainSysInfo {-1}
	set_connection_parameter_value clock_in.out_clk/add_fpga_ip_export_1_di_0.clock clockRateSysInfo {50000000.0}
	set_connection_parameter_value clock_in.out_clk/add_fpga_ip_export_1_di_0.clock clockResetSysInfo {}
	set_connection_parameter_value clock_in.out_clk/add_fpga_ip_export_1_di_0.clock resetDomainSysInfo {-1}
	add_connection clock_in.out_clk/add_fpga_ip_export_1_di_0.clock2x
	set_connection_parameter_value clock_in.out_clk/add_fpga_ip_export_1_di_0.clock2x clockDomainSysInfo {-1}
	set_connection_parameter_value clock_in.out_clk/add_fpga_ip_export_1_di_0.clock2x clockRateSysInfo {50000000.0}
	set_connection_parameter_value clock_in.out_clk/add_fpga_ip_export_1_di_0.clock2x clockResetSysInfo {}
	set_connection_parameter_value clock_in.out_clk/add_fpga_ip_export_1_di_0.clock2x resetDomainSysInfo {-1}
	add_connection clock_in.out_clk/master_0.clk
	set_connection_parameter_value clock_in.out_clk/master_0.clk clockDomainSysInfo {-1}
	set_connection_parameter_value clock_in.out_clk/master_0.clk clockRateSysInfo {50000000.0}
	set_connection_parameter_value clock_in.out_clk/master_0.clk clockResetSysInfo {}
	set_connection_parameter_value clock_in.out_clk/master_0.clk resetDomainSysInfo {-1}
	add_connection clock_in.out_clk/reset_in.clk
	set_connection_parameter_value clock_in.out_clk/reset_in.clk clockDomainSysInfo {-1}
	set_connection_parameter_value clock_in.out_clk/reset_in.clk clockRateSysInfo {50000000.0}
	set_connection_parameter_value clock_in.out_clk/reset_in.clk clockResetSysInfo {}
	set_connection_parameter_value clock_in.out_clk/reset_in.clk resetDomainSysInfo {-1}
	add_connection master_0.master/add_fpga_ip_export_1_di_0.csr_ring_root_avs
	set_connection_parameter_value master_0.master/add_fpga_ip_export_1_di_0.csr_ring_root_avs addressMapSysInfo {}
	set_connection_parameter_value master_0.master/add_fpga_ip_export_1_di_0.csr_ring_root_avs addressWidthSysInfo {}
	set_connection_parameter_value master_0.master/add_fpga_ip_export_1_di_0.csr_ring_root_avs arbitrationPriority {1}
	set_connection_parameter_value master_0.master/add_fpga_ip_export_1_di_0.csr_ring_root_avs baseAddress {0x0000}
	set_connection_parameter_value master_0.master/add_fpga_ip_export_1_di_0.csr_ring_root_avs defaultConnection {0}
	set_connection_parameter_value master_0.master/add_fpga_ip_export_1_di_0.csr_ring_root_avs domainAlias {}
	set_connection_parameter_value master_0.master/add_fpga_ip_export_1_di_0.csr_ring_root_avs qsys_mm.burstAdapterImplementation {GENERIC_CONVERTER}
	set_connection_parameter_value master_0.master/add_fpga_ip_export_1_di_0.csr_ring_root_avs qsys_mm.clockCrossingAdapter {HANDSHAKE}
	set_connection_parameter_value master_0.master/add_fpga_ip_export_1_di_0.csr_ring_root_avs qsys_mm.enableAllPipelines {FALSE}
	set_connection_parameter_value master_0.master/add_fpga_ip_export_1_di_0.csr_ring_root_avs qsys_mm.enableEccProtection {FALSE}
	set_connection_parameter_value master_0.master/add_fpga_ip_export_1_di_0.csr_ring_root_avs qsys_mm.enableInstrumentation {FALSE}
	set_connection_parameter_value master_0.master/add_fpga_ip_export_1_di_0.csr_ring_root_avs qsys_mm.insertDefaultSlave {FALSE}
	set_connection_parameter_value master_0.master/add_fpga_ip_export_1_di_0.csr_ring_root_avs qsys_mm.interconnectResetSource {DEFAULT}
	set_connection_parameter_value master_0.master/add_fpga_ip_export_1_di_0.csr_ring_root_avs qsys_mm.interconnectType {STANDARD}
	set_connection_parameter_value master_0.master/add_fpga_ip_export_1_di_0.csr_ring_root_avs qsys_mm.maxAdditionalLatency {1}
	set_connection_parameter_value master_0.master/add_fpga_ip_export_1_di_0.csr_ring_root_avs qsys_mm.optimizeRdFifoSize {FALSE}
	set_connection_parameter_value master_0.master/add_fpga_ip_export_1_di_0.csr_ring_root_avs qsys_mm.piplineType {PIPELINE_STAGE}
	set_connection_parameter_value master_0.master/add_fpga_ip_export_1_di_0.csr_ring_root_avs qsys_mm.responseFifoType {REGISTER_BASED}
	set_connection_parameter_value master_0.master/add_fpga_ip_export_1_di_0.csr_ring_root_avs qsys_mm.syncResets {FALSE}
	set_connection_parameter_value master_0.master/add_fpga_ip_export_1_di_0.csr_ring_root_avs qsys_mm.widthAdapterImplementation {GENERIC_CONVERTER}
	set_connection_parameter_value master_0.master/add_fpga_ip_export_1_di_0.csr_ring_root_avs slaveDataWidthSysInfo {-1}
	add_connection master_0.master_reset/add_fpga_ip_export_1_di_0.resetn
	set_connection_parameter_value master_0.master_reset/add_fpga_ip_export_1_di_0.resetn clockDomainSysInfo {-1}
	set_connection_parameter_value master_0.master_reset/add_fpga_ip_export_1_di_0.resetn clockResetSysInfo {}
	set_connection_parameter_value master_0.master_reset/add_fpga_ip_export_1_di_0.resetn resetDomainSysInfo {-1}
	add_connection reset_in.out_reset/add_fpga_ip_export_1_di_0.resetn
	set_connection_parameter_value reset_in.out_reset/add_fpga_ip_export_1_di_0.resetn clockDomainSysInfo {-1}
	set_connection_parameter_value reset_in.out_reset/add_fpga_ip_export_1_di_0.resetn clockResetSysInfo {}
	set_connection_parameter_value reset_in.out_reset/add_fpga_ip_export_1_di_0.resetn resetDomainSysInfo {-1}
	add_connection reset_in.out_reset/master_0.clk_reset
	set_connection_parameter_value reset_in.out_reset/master_0.clk_reset clockDomainSysInfo {-1}
	set_connection_parameter_value reset_in.out_reset/master_0.clk_reset clockResetSysInfo {}
	set_connection_parameter_value reset_in.out_reset/master_0.clk_reset resetDomainSysInfo {-1}

	# add the exports
	set_interface_property exception_add EXPORT_OF add_fpga_ip_export_1_di_0.device_exception_bus
	set_interface_property irq_add EXPORT_OF add_fpga_ip_export_1_di_0.kernel_irqs
	set_interface_property clk EXPORT_OF clock_in.in_clk
	set_interface_property reset EXPORT_OF reset_in.in_reset

	# set values for exposed HDL parameters
	set_domain_assignment master_0.master qsys_mm.burstAdapterImplementation GENERIC_CONVERTER
	set_domain_assignment master_0.master qsys_mm.clockCrossingAdapter HANDSHAKE
	set_domain_assignment master_0.master qsys_mm.enableAllPipelines FALSE
	set_domain_assignment master_0.master qsys_mm.enableEccProtection FALSE
	set_domain_assignment master_0.master qsys_mm.enableInstrumentation FALSE
	set_domain_assignment master_0.master qsys_mm.insertDefaultSlave FALSE
	set_domain_assignment master_0.master qsys_mm.interconnectResetSource DEFAULT
	set_domain_assignment master_0.master qsys_mm.interconnectType STANDARD
	set_domain_assignment master_0.master qsys_mm.maxAdditionalLatency 1
	set_domain_assignment master_0.master qsys_mm.optimizeRdFifoSize FALSE
	set_domain_assignment master_0.master qsys_mm.piplineType PIPELINE_STAGE
	set_domain_assignment master_0.master qsys_mm.responseFifoType REGISTER_BASED
	set_domain_assignment master_0.master qsys_mm.syncResets FALSE
	set_domain_assignment master_0.master qsys_mm.widthAdapterImplementation GENERIC_CONVERTER

	# set the the module properties
	set_module_property BONUS_DATA {<?xml version="1.0" encoding="UTF-8"?>
<bonusData>
 <element __value="add_fpga_ip_export_1_di_0">
  <datum __value="_sortIndex" value="3" type="int" />
 </element>
 <element __value="clock_in">
  <datum __value="_sortIndex" value="0" type="int" />
 </element>
 <element __value="master_0">
  <datum __value="_sortIndex" value="2" type="int" />
 </element>
 <element __value="reset_in">
  <datum __value="_sortIndex" value="1" type="int" />
 </element>
</bonusData>
}
	set_module_property FILE {add_kernel_wrapper.qsys}
	set_module_property GENERATION_ID {0x00000000}
	set_module_property NAME {add_kernel_wrapper}

	# save the system
	sync_sysinfo_parameters
	save_system add_kernel_wrapper
}

proc do_set_exported_interface_sysinfo_parameters {} {
}

# create all the systems, from bottom up
do_create_add_kernel_wrapper

# set system info parameters on exported interface, from bottom up
do_set_exported_interface_sysinfo_parameters
