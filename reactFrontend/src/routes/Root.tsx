import Page from "../components/Page";
import { useDvdScreensaver } from "react-dvd-screensaver";
import check24Logo from "../assets/check24-logo.svg";
import "../css/Root.css";
import { RefObject } from "react";

// The root of the website
// TODO: pretty up
function Root() {
  const dvdScreensaver = useDvdScreensaver({ speed: 3 });

  const content = (
    <div className="contentBody">
      <h1>Find skilled craftsmen in your area!</h1>
      <div
        ref={dvdScreensaver.containerRef as RefObject<HTMLDivElement>}
        style={{ width: "100%", height: "70%" }}
      >
        <div
          ref={dvdScreensaver.elementRef as RefObject<HTMLDivElement>}
          style={{ width: "8%", height: "auto" }}
        >
          <img src={check24Logo} />
        </div>
      </div>
    </div>
  );

  return <Page content={content} />;
}

export default Root;
