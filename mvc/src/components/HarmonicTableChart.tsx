import * as React from 'react';

interface HarmonicTableChartProps {
    data: {x: number; y: number}[];
}

export default function HarmonicTableChart(props: HarmonicTableChartProps) {

    let renderRows = function() {
        let rows = [];
        for (let point of props.data) {
            rows.push(<tr><td>{point.x}</td><td>{point.y}</td></tr>);
        }
        return (<tbody>{rows}</tbody>);
    };

    return (
        <table>
            <thead>
                <th><td>X</td><td>Y</td></th>
            </thead>
            {renderRows()}
        </table>);
}