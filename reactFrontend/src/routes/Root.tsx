import Page from "../components/Page";
import { useDvdScreensaver } from "react-dvd-screensaver";
import check24Logo from "../assets/check24-logo.svg";
import "../css/Root.css";
import { RefObject, useEffect, useState } from "react";

export const COLORS = [
  "#ff0000",
  "#ff4000",
  "#ff8000",
  "#ffbf00",
  "#ffff00",
  "#bfff00",
  "#80ff00",
  "#40ff00",
  "#00ff00",
  "#00ff40",
  "#00ff80",
  "#00ffbf",
  "#00ffff",
  "#00bfff",
  "#0080ff",
  "#0040ff",
  "#0000ff",
  "#4000ff",
  "#8000ff",
  "#bf00ff",
  "#ff00ff",
  "#ff00bf",
  "#ff0080",
  "#ff0040",
  "#ff0000",
] as const;

// The root of the website
// TODO: pretty up
function Root() {
  const dvdScreensaver = useDvdScreensaver({ speed: 5 });
  const [logoColor, setLogoColor] = useState<string>(COLORS[0]);
  useEffect(() => {
    setLogoColor(COLORS[Math.floor(Math.random() * COLORS.length)]);
  }, [dvdScreensaver.impactCount]);

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
          {/* st0{fill:#FFFFFF;} -> logoColor */}
          <img
            src={check24Logo}
            style={{ fill: logoColor }}
          />
        </div>
      </div>
    </div>
  );

  return <Page content={content} />;
}

export default Root;
