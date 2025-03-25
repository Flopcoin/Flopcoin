## 🪙 Flopcoin Core v2.0.0.0 Release Notes  
**Release Date:** March 25, 2025  
**Network Compatibility:** Prepares for upcoming v2.0.0.0 hard fork at block height **120000**  


## 🎉 Overview

This is a **mandatory hard fork upgrade** for all Flopcoin nodes, pools, and wallets. It introduces a new block validation consensus, a secure and time-limited developer fee mechanism, and protections against cross-chain interference.

---

## 📊 Key Changes

### ✅ Hard Fork Activation

- **Fork Height:** `V2_0ForkHeight`
- **Purpose:** Activates dev fee enforcement, modifies coinbase structure, and transitions to new network parameters.

### 🚜 New `messageStart` Magic Bytes

To isolate Flopcoin from other coins (like Dogecoin):

```cpp
pchMessageStart[0] = 0xfa;
pchMessageStart[1] = 0xbf;
pchMessageStart[2] = 0xb5;
pchMessageStart[3] = 0xda;
```

**Note:** This change activates at fork height. Nodes not upgraded will be disconnected from the network.

---

## 📉 Developer Fee Implementation

- **Amount:** `chainparams.GetDevFeePercentage()` (e.g., 5% or 10%) of block subsidy
- **Start Height:** `V2_0ForkHeight`
- **End Height:** `nDevFeeEndHeight` (e.g., block 600,000)
- **Enforced In:**
  - `miner.cpp` (coinbase transaction creation)
  - `validation.cpp` (block validation logic)
  - `rpc/mining.cpp` (exposes fee info via `getblocktemplate`)

Blocks with incorrect dev fee (too low or too high) are rejected with ban score penalties.

---

## ⚖️ Dev Fee Enforcement Logic

- **Validated** in `ConnectBlock()`:
  - Verifies correct payee address.
  - Verifies fee amount matches expected percentage.
  - Rejects blocks with incorrect or missing dev fee.
- **Ban Score:** 200 (default) for invalid submissions.

---

## 📈 `getblocktemplate` Enhancements

To assist mining pools with dev fee compliance:

- `devfee`: includes payee address and exact amount.
- `devfee_payments_running`: `true` or `false`
- `devfee_start_height`: value of `V2_0ForkHeight`
- `devfee_end_height`: value of `nDevFeeEndHeight`
- `devfee_percentage`: the enforced dev fee percentage (e.g., 10)

Pools can dynamically support the dev fee window without hardcoded logic.

---

## 🛡️ Stratum Mining Compatibility

Mining pools using coinbase builders (e.g., `coinbase.cpp`) should:

- Parse the new RPC fields in `getblocktemplate`
- Dynamically include the `devfee` output only if `devfee_payments_running == true`
- Stop inserting the dev fee after `devfee_end_height`

> A log message is shown once: `"FLOP Dev fee payments disabled at block 600000. Full rewards to miners."`

---

## 🚨 Security Notes

- Modifying the dev fee percentage in source code **does not bypass validation**.
- Blocks with incorrect dev fee amounts are **rejected and nodes banned**.
- After `nDevFeeEndHeight`, any dev fee output causes the block to be rejected.

---

🛑 Protocol Enforcement

Minimum protocol version raised to 70016.

Nodes running older protocol versions will be disconnected to prevent outdated communication or invalid block relaying.

---

## 🚀 Final Notes

This release ensures:

- Transparent and time-limited Dev fee funding.
- Full rewards return to miners after a fixed point.
- Soft and hard fork protections.

---

## 📅 Upgrade Instructions

1. Backup your `wallet.dat`.
2. Stop Flopcoin daemon.
3. Replace old binaries with v2.0.0.0.
4. Restart daemon.
5. Ensure peers are running v2.0.0.0 or higher.

---

## 🌐 Versioning

- **Version:** `v2.0.0.0`
- **Protocol:** updated
- **Network:** new `messageStart`




