import * as React from 'react';
import LineChart from 'react-linechart';
import '../../node_modules/react-linechart/dist/styles.css';

interface HarmonicLineChartProps {
    data: {x: number; y: number}[];
}

export default function HarmonicLineChart(props: HarmonicLineChartProps) {
    const data = [
        {
            color: 'steelblue',
            points: props.data
        }
    ];
    return (
        <LineChart yMin={-5} yMax={5} width={984} height={400} data={data} />
    );
}