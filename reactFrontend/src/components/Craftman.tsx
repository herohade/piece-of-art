type Props = {
  id: number;
  name: string;
  rankingScore: number;
};

// Navigation bar at the bottom of the page
function Craftman({ id, name, rankingScore }: Props) {
  return <>
    <div className="craftman">
      <h2>{name} ({id})</h2>
      <p>Ranking score: {rankingScore} / 100</p>
    </div>
  </>;
}

export default Craftman;
