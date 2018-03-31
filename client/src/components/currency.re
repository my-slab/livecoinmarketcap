let component = ReasonReact.statelessComponent("Currency");

let make = (~coin: Coin.coin, _children) => {
  ...component,
  render: _self =>
    <tr>

        <td> <Int value=coin.rank /> </td>
        <td> <Text value=coin.name /> </td>
        <td> <Fiat value=coin.market_cap_usd /> </td>
        <td> <Fiat value=coin.price /> </td>
        <td> <Fiat value=coin.hour_volume_24h /> </td>
        <td>
          <Float value=coin.available_supply />
          <Text value=" " />
          <Text value=coin.symbol />
        </td>
      </tr>
      /* <td> <Percentage value=coin.percent_change_24h /> </td> */
};