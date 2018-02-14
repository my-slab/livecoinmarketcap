let component = ReasonReact.statelessComponent("Page");

let make = (~message: string, _children) => {
  ...component,
  render: _self =>
    <div>
      <div> <h1> (ReasonReact.stringToElement(message)) </h1> </div>
      <Table />
    </div>
};