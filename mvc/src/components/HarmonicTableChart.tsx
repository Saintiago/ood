import * as React from 'react';
import {
    Table,
    TableBody,
    TableHeader,
    TableHeaderColumn,
    TableRow,
    TableRowColumn,
} from 'material-ui';

interface HarmonicTableChartProps {
    data: {x: number; y: number}[];
}

export default function HarmonicTableChart(props: HarmonicTableChartProps) {

    let renderRows = function() {
        let rows = [];
        let i = 0;
        for (let point of props.data) {
            rows.push(
                <TableRow key={i++}>
                    <TableRowColumn>{point.x}</TableRowColumn>
                    <TableRowColumn>{point.y}</TableRowColumn>
                </TableRow>);
        }
        return (
            <TableBody
                displayRowCheckbox={false}
                deselectOnClickaway={false}
                showRowHover={false}
                stripedRows={true}
            >
                {rows}
            </TableBody>
        );
    };

    return (
        <Table
            selectable={false}
            multiSelectable={false}
        >
            <TableHeader
                displaySelectAll={false}
                adjustForCheckbox={false}
                enableSelectAll={false}
            >
                <TableRow>
                    <TableHeaderColumn tooltip="X Axis">X Axis</TableHeaderColumn>
                    <TableHeaderColumn tooltip="Y Axis">Y Axis</TableHeaderColumn>
                </TableRow>
            </TableHeader>
            {renderRows()}
        </Table>);
}