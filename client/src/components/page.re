type state = {offset: int};

type action =
  | Navigate(int);

let component = ReasonReact.reducerComponent("Page");

let make = (~title: string, _children) => {
  ...component,
  initialState: () => {offset: 0},
  reducer: (action, _state) =>
    switch action {
    | Navigate(offset) => ReasonReact.Update({offset: offset})
    },
  subscriptions: self => [
    Sub(
      () =>
        ReasonReact.Router.watchUrl(url => {
          Js.log("--------");
          Js.log(url.search);
          Js.log("--------");
          switch url.search {
          | _ => self.send(Navigate(20))
          };
        }),
      ReasonReact.Router.unwatchUrl
    )
  ],
  render: _self =>
    <div>
      <div> <h1> <Text value=title /> </h1> </div>
      <Table />
      <br />
      <Pagination />
    </div>
};