<h1 align="center">
<img src="https://i.imgur.com/FSQgWZq.png" alt="Flopcoin" width="300"/>
<br/><br/>
Flopcoin Core [FLOP, F]
</h1>
Flopcoin is a layer 1, no-premine, decentralized cryptocurrency that launched on December 9th, 2024. It was forked from Dogecoin and is secured with proof-of-work mining using the scrypt algorithm. his means there are no liquidity pools to drain, no blacklisting wallets, and no confusing smart contracts. Flopcoin is a simple blockchain for the people, by the people.
<br/><br/>
The name "Flopcoin" is an homage to the "Floptropica" meme community and thus is considered a memecoin. Beyond being just a store of value or a digital currency, we hope to integrate Flopcoin into a tipping platform that spans across all social media services to allow rewarding your favorite content creators.
<br/><br/>
The Flopcoin Core software allows anyone to operate a node in the Flopcoin blockchain network and use the Scrypt hashing method for Proof of Work. It is adapted from Dogecoin Core, Bitcoin Core, and other cryptocurrencies.
<br/><br/>
For information about the default fees used on the Flopcoin network, please
refer to the [fee recommendation](doc/fee-recommendation.md).
<br/><br/>

**Website:** [https://flopcoin.lovable.app](https://flopcoin.lovable.app)

## Dogecoin Differences

Flopcoin is a fork of Dogecoin. For the sake of familiarity, we will attempt to keep Flopcoin similar to Dogecoin.

Changes:

* Addresses start with `F` instead of `D`
* GUI themed for Flopcoin

* Coin Name    : Flopcoin
* Coin ticker  : FLOP
* Algorithm    : Scrypt
* Block Time   : 60 seconds
* Default Port : 32552
* Explorer 1   : https://explorer.flopcoin.net
* github       : https://github.com/Flopcoin/Flopcoin
* Wallet       : https://github.com/Flopcoin/Flopcoin/releases


## Usage 💻

To start your journey with Flopcoin Core, see the [installation guide](INSTALL.md) and the [getting started](doc/getting-started.md) tutorial.

The JSON-RPC API provided by Flopcoin Core is self-documenting and can be browsed with `flopcoin-cli help`, while detailed information for each command can be viewed with `flopcoin-cli help <command>`. Alternatively, see the [Bitcoin Core documentation](https://developer.bitcoin.org/reference/rpc/) - which implement a similar protocol - to get a browsable version.

<font face="Verdana"><b>Block Rewards Distribution</b></font>
&nbsp;</p>
<table border="1" width="46%">
	<tr>
		<td width="230"><b>Starting Block</b></td>
		<td width="270"><b>End Block</b></td>
		<td><b>Rewards</b></td>
	</tr>
	<tr>
		<td width="230">1</td>
		<td width="270">99,999</td>
		<td>500,000</td>
	</tr>
	<tr>
		<td width="230">100,000</td>
		<td width="270">199,999</td>
		<td>250,000</td>
	</tr>
	<tr>
		<td width="230">200,000</td>
		<td width="270">299,999</td>
		<td>125,000</td>
	</tr>
	<tr>
		<td width="230">300,000</td>
		<td width="270">399,999</td>
		<td>62,500</td>
	</tr>
	<tr>
		<td width="230">400,000</td>
		<td width="270">499,999</td>
		<td>31,250</td>
	</tr>
	<tr>
		<td width="230">500,000</td>
		<td width="270">599,999</td>
		<td>15,625</td>
	</tr>
	<tr>
		<td width="230">600,000</td>
		<td width="270">unlimited supply</td>
		<td>10,000</td>
	</tr>
</table>

<font face="Verdana"><b>Running a Full Node</b></font>

Running a full node helps contribute to the Flopcoin network's security and decentralization by relaying data to other nodes and verifying transactions. If you would like to run a full node, simply download the Flopcoin Core wallet, let the blockchain fully sync, and ensure your network has port 32552 forwarded to allow incoming connections. 
&nbsp;</p>
<table border="1" width="46%">
	<tr>
		<td width="230"><b>Default Port</b></td>
		<td width="270">32552</td>
	</tr>
</table>

## Ongoing development 💻

Flopcoin Core is an open source and community driven software. The development
process is open and publicly visible; anyone can see, discuss and work on the
software.

Main development resources:

* [GitHub Projects](https://github.com/Flopcoin/Flopcoin/projects) is used to
  follow planned and in-progress work for upcoming releases.
* [GitHub Discussion](https://github.com/Flopcoin/Flopcoin/discussions) is used
  to discuss features, planned and unplanned, related to both the development of
  the Flopcon Core software, the underlying protocols and the FLOP asset.


### Version strategy
Version numbers are following ```major.minor.patch``` semantics.

### Branches
There are 3 types of branches in this repository:

- **master:** Stable, contains the latest version of the latest *major.minor* release.
- **maintenance:** Stable, contains the latest version of previous releases, which are still under active maintenance. Format: ```<version>-maint```
- **development:** Unstable, contains new code for planned releases. Format: ```<version>-dev```

*Master and maintenance branches are exclusively mutable by release. Planned*
*releases will always have a development branch and pull requests should be*
*submitted against those. Maintenance branches are there for **bug fixes only,***
*please submit new features against the development branch with the highest version.*

## Contributing 🤝

If you find a bug or experience issues with this software, please report it
using the [issue system](https://github.com/Flopcoin/Flopcoin/issues).

Please see [the contribution guide](CONTRIBUTING.md) to see how you can
participate in the development of Flopcoin Core. There are often
[topics seeking help](https://github.com/Flopcoin/Flopcoin/labels/help%20wanted)
where your contributions will have high impact and get very appreciation.

## Communities 🐸

You can join the communities on different social media.
To see what's going on, meet people & discuss, find the latest meme, learn
about Flopcoin, give or ask for help, to share your project.

Here are some places to visit:


* [Discord](https://discord.gg/8qJqXQaczJ)
* [Website](https://flopcoin.lovable.app)
* [X](https://x.com/flopcoin_dev)

## Future Plan

- Securing the network with more mining pools
- Getting Flopcoin listed on popular exchanges
- Implementing a content creator tipping platform using Flopcoin as payment.
- Anything the community is interested in!

## Frequently Asked Questions ❓

Do you have a question regarding Flopcoin? An answer is perhaps already in the [FAQ](doc/FAQ.md) or the [Q&A section](https://github.com/Flopcoin/Flopcoin/discussions/categories/q-a) of the discussion board!

## License ⚖️
Flopcoin Core is released under the terms of the MIT license. See
[COPYING](COPYING) for more information or see
[opensource.org](https://opensource.org/licenses/MIT)
