let component = ReasonReact.statelessComponent("Percentage");

let toCurrency: float => string = [%bs.raw
  {|
    function(value) {
      const number = Number(value);
      const { language = 'us-US' } = navigator;

      return number > 1 ?
        number.toLocaleString(language, { style: 'currency', currency: 'USD' }) :
        'US$' + number;
    }
  |}
];

let make = (~value: float, _children) => {
  ...component,
  render: _self => <span> <Text value=(toCurrency(value)) /> </span>
};