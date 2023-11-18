import "../css/NavBar.css";
import HeaderBar from "./HeaderBar";
import NavBar from "./NavBar";

type Props = {
  content: JSX.Element;
};

// Navigation bar at the bottom of the page
function Page({ content }: Props) {
  return (
    <>
      <HeaderBar />
      {content}
      <NavBar />
    </>
  );
}

export default Page;
