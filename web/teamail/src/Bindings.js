// TODO: remove hack to avoid tree-shaking - get this off |window|.
window.getString = () => {
  return "Not really fetch";
}