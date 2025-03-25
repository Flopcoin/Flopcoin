## 🪙 Flopcoin Core v1.3.1.0 Release Notes  
**Release Date:** March 23, 2025  
**Network Compatibility:** Prepares for upcoming v2.0.0.0 hard fork at block height **115000**  

---

### 🚀 Overview

Flopcoin v1.3.1.0 is a minor but critical update that builds on v1.3.0.1 by introducing final safeguards before the mandatory **v2.0.0.0 hard fork**. This version includes proactive user alerts, automatic peer disconnection logic, mining halt mechanisms, and GUI messaging to ensure no node continues on the legacy chain after the fork height.

---

### 🆕 Changes in v1.3.1.0

- 🔐 **Network Lockdown at Fork Height**
  - At block height `V2_0ForkHeight - 1`, nodes will:
    - Disconnect from all peers.
    - Disable all further network activity.
    - Halt any mining operations by rejecting block creation.
    - Display a final warning in GUI, RPC, and logs.

- 🧠 **Block Creation Prevention**
  - `BlockAssembler::CreateNewBlock()` now rejects mining new blocks past the fork height, ensuring old clients can't produce invalid post-fork blocks.

- 💬 **Dynamic UI Warnings**
  - Updated `clientmodel.cpp` and `overviewpage.cpp` to show real-time alerts:
    - Displays countdown messages when the fork height is approaching.
    - Shows upgrade instructions with clickable GitHub links.
    - Final alert at block `V2_0ForkHeight - 1` to inform users the version is no longer supported.

- 🔌 **Thread-Safe Peer Disconnection**
  - New logic added to `net.cpp` (`CheckForkDisconnect()`) to monitor block height and automatically disconnect all peers and disable networking once fork height is reached.

---

### ✅ Carried Over from v1.3.0.1

- 🧮 Added `getversionbitsinfo`, `getdifficultyalgo`, and `isauxpowenabled` RPCs.
- 🧠 Improved soft fork detection and BIP34/65/66 enforcement.
- ⛓️ Version Bits 3–28 disabled for security.
- 🔐 Rebased checkpoints and synced block header metadata.
- 🛠️ Minor optimizations and safety improvements to the consensus layer.

---

### ⚠️ Important Notice

This is the **last supported version before v2.0.0.0**.  
If your node reaches block height **115000** on this version, it will no longer sync, mine, or communicate with other peers.  
**Please upgrade to v2.0.0.0 immediately after that block height.**

👉 Download the v1.3.1.0 release:  
https://github.com/Flopcoin/Flopcoin/releases/v1.3.1.0

