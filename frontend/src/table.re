let component = ReasonReact.statelessComponent("Table");

let make = _children => {
  ...component,
  render: _self =>
    <table>
      <thead>
        <tr>
          <th> (ReasonReact.stringToElement("#")) </th>
          <th> (ReasonReact.stringToElement("Name")) </th>
          <th> (ReasonReact.stringToElement("Market Cap")) </th>
          <th> (ReasonReact.stringToElement("Price")) </th>
          <th> (ReasonReact.stringToElement("Volume (24h)")) </th>
          <th> (ReasonReact.stringToElement("Circulating Supply")) </th>
          <th> (ReasonReact.stringToElement("Change (24h)")) </th>
        </tr>
      </thead>
      <Currencies />
    </table>
};