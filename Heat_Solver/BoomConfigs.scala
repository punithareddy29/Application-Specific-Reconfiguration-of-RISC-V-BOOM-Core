package chipyard

import freechips.rocketchip.config.{Config}

// ---------------------
// BOOM Configs
// ---------------------

class SmallBoomConfig extends Config( 
  // new boom.common.WithNBoomPerfCounters(15) ++
  new chipyard.config.WithNPerfCounters ++
  // new boom.common.WithTAGELBPD ++ 
  new boom.common.WithBoom2BPD ++
  // new boom.common.WithAlpha21264BPD ++
  new boom.common.WithNSmallBooms(1) ++                          // small boom config
  new chipyard.config.AbstractConfig)

class CS152BoomConfig extends Config(
  new boom.common.WithNBoomPerfCounters(11) ++
  new boom.common.WithTAGELBPD ++
  new boom.common.WithNCS152DefaultBooms(1) ++                          // small boom config
  new chipyard.config.AbstractConfig)  
  
class MediumBoomConfig extends Config(
  new boom.common.WithNMediumBooms(1) ++                         // medium boom config
  new chipyard.config.AbstractConfig)

class LargeBoomConfig extends Config(
  new boom.common.WithNBoomPerfCounters(11) ++
  new boom.common.WithTAGELBPD ++
  new boom.common.WithNLargeBooms(1) ++                          // large boom config
  new chipyard.config.AbstractConfig)

class MegaBoomConfig extends Config(
  new boom.common.WithNMegaBooms(1) ++                           // mega boom config
  new chipyard.config.AbstractConfig)

class DualSmallBoomConfig extends Config(
  new boom.common.WithNSmallBooms(2) ++                          // 2 boom cores
  new chipyard.config.AbstractConfig)

class HwachaLargeBoomConfig extends Config(
  new chipyard.config.WithHwachaTest ++
  new hwacha.DefaultHwachaConfig ++                              // use Hwacha vector accelerator
  new boom.common.WithNLargeBooms(1) ++
  new chipyard.config.AbstractConfig)

class LoopbackNICLargeBoomConfig extends Config(
  new chipyard.harness.WithLoopbackNIC ++                        // drive NIC IOs with loopback
  new icenet.WithIceNIC ++                                       // build a NIC
  new boom.common.WithNLargeBooms(1) ++
  new chipyard.config.AbstractConfig)

class DromajoBoomConfig extends Config(
  new chipyard.harness.WithSimDromajoBridge ++                   // attach Dromajo
  new chipyard.config.WithTraceIO ++                             // enable the traceio
  new boom.common.WithNSmallBooms(1) ++
  new chipyard.config.AbstractConfig)

class ECE5504NoPredSmallBoomConfig extends Config(
  new boom.common.WithNBoomPerfCounters(11) ++
  new boom.common.WithNSmallBooms(1) ++                          // small boom config
  new chipyard.config.AbstractConfig)

class ECE5504SWPredSmallBoomConfig extends Config(
  new boom.common.WithSWBPD ++
  new boom.common.WithNBoomPerfCounters(11) ++
  new boom.common.WithNSmallBooms(1) ++                          // small boom config
  new chipyard.config.AbstractConfig)

class ECE5504TAGEPredSmallBoomConfig extends Config(
  new boom.common.WithTAGELBPD ++
  new boom.common.WithNBoomPerfCounters(11) ++
  new boom.common.WithNSmallBooms(1) ++                          // small boom config
  new chipyard.config.AbstractConfig)

class ECE5504GsharePredSmallBoomConfig extends Config(
  new boom.common.WithBoom2BPD ++
  new boom.common.WithNBoomPerfCounters(11) ++
  new boom.common.WithNSmallBooms(1) ++                          // small boom config
  new chipyard.config.AbstractConfig)

class ECE5504AlphaPredSmallBoomConfig extends Config(
  new boom.common.WithAlpha21264BPD ++
  new boom.common.WithNBoomPerfCounters(11) ++
  new boom.common.WithNSmallBooms(1) ++                          // small boom config
  new chipyard.config.AbstractConfig)