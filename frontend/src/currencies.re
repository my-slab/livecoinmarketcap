let component = ReasonReact.statelessComponent("Currencies");

let make = _children => {
  ...component,
  render: _self =>
    <tbody>
      <tr>
        <td> (ReasonReact.stringToElement("1")) </td>
        <td> (ReasonReact.stringToElement("Bitcoin")) </td>
        <td> (ReasonReact.stringToElement("$139,936,962,941")) </td>
        <td> (ReasonReact.stringToElement("$8,302.61")) </td>
        <td> (ReasonReact.stringToElement("$8,378,290,000")) </td>
        <td> (ReasonReact.stringToElement("16,854,575 BTC")) </td>
        <td> (ReasonReact.stringToElement("-2.03%")) </td>
      </tr>
    </tbody>
};