let component = ReasonReact.statelessComponent("Coin");

let make = (coin: Currencies.coin, _children) => {
  ...component,
  render: _self =>
    <tr key=coin.name>
      <td> (ReasonReact.stringToElement(coin.rank)) </td>
      <td> (ReasonReact.stringToElement(coin.name)) </td>
      <td> (ReasonReact.stringToElement(coin.market_cap_usd)) </td>
      <td> (ReasonReact.stringToElement(coin.price)) </td>
      <td> (ReasonReact.stringToElement(coin.hour_volume_24h)) </td>
      <td> (ReasonReact.stringToElement(coin.available_supply)) </td>
      <td> (ReasonReact.stringToElement(coin.percent_change_24h)) </td>
    </tr>
};