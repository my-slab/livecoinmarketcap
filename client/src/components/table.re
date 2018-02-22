type action =
  | Click(string, Sort.direction);

type state = {
  direction: Sort.direction,
  key: string
};

type column = {
  display: string,
  key: string
};

let component = ReasonReact.reducerComponent("Table");

let columns = [
  {display: "#", key: "rank"},
  {display: "Name", key: "name"},
  {display: "Market Cap", key: "market_cap_usd"},
  {display: "Price", key: "price"},
  {display: "Volume (24h)", key: "24h_volume_usd"},
  {display: "Circulating Supply", key: "available_supply"},
  {display: "Change (24h)", key: "percent_change_24h"}
];

let make = _children => {
  ...component,
  initialState: () => {
    key: columns |> List.hd |> (column => column.key),
    direction: Desc
  },
  reducer: (action, state) =>
    switch action {
    | Click(key, direction) =>
      key == state.key ?
        ReasonReact.Update({direction: Sort.toggle(direction), key}) :
        ReasonReact.Update({direction: Desc, key})
    },
  render: self =>
    <table>
      <thead>
        <tr>
          (
            columns
            |> List.map(column =>
                 <th
                   key=column.key
                   onClick=(
                     event => {
                       ReactEventRe.Mouse.preventDefault(event);
                       self.send(Click(column.key, self.state.direction));
                     }
                   )>
                   (
                     self.state.key == column.key ?
                       <Sort direction=self.state.direction /> :
                       ReasonReact.nullElement
                   )
                   <Text value=column.display />
                 </th>
               )
            |> Array.of_list
            |> ReasonReact.arrayToElement
          )
        </tr>
      </thead>
      <Currencies
        columns=(List.length(columns))
        direction=self.state.direction
        sort_by=self.state.key
      />
    </table>
};