#include <numeric>
#include "Utils.cpp"

int min(
    std::vector<std::vector<int>> &adjactive_matrix,
    int &previous_value,
    int &row,
    int &column
)
{
    if (previous_value == -1)
    {
        return adjactive_matrix[row][column];
    }
    else
    {
        if (adjactive_matrix[row][column] != -1 && adjactive_matrix[row][column] < previous_value)
        {
            return adjactive_matrix[row][column];
        }
        else
        {
            return previous_value;
        }
    }
}

std::vector<int> find_min_values(std::vector<std::vector<int>> &adjactive_matrix, bool from_row)
{
    std::vector<int> min_values;
    for (int i = 0; i < adjactive_matrix.size(); i++)
    {
        int min_value = -1;
        for (int k = 0; k < adjactive_matrix.size(); k++)
        {
            if (from_row)
            {
                min_value = min(adjactive_matrix, min_value, i, k);
            }
            else
            {
                min_value = min(adjactive_matrix, min_value, k, i);
            }
        }
        min_values.push_back(min_value);
    }
    return min_values;
}

void subtract_min(
    std::vector<std::vector<int>> &adjactive_matrix,
    std::vector<int> min_values,
    bool from_row
)
{
    for (int i = 0; i < adjactive_matrix.size(); i++)
    {
        for (int k = 0; k < adjactive_matrix.size(); k++)
        {
            if (from_row)
            {
                if (adjactive_matrix[k][i] < 0) continue;
                adjactive_matrix[k][i] = adjactive_matrix[k][i] - min_values[k];
            }
            else
            {
                if (adjactive_matrix[i][k] < 0) continue;
                adjactive_matrix[i][k] = adjactive_matrix[i][k] - min_values[k];
            }
        }
    }
}

struct MatrixElement
{
    int row;
    int column;
    int value;

    MatrixElement(int row, int column, int value)
    {
        this->row = row;
        this->column = column;
        this->value = value;
    }

};

MatrixElement* calculate_max_penalty(
    std::vector<std::vector<int>> &adjactive_matrix,
    std::vector<int> min_row_value,
    std::vector<int> min_column_values
)
{
    MatrixElement *max_penalty = new MatrixElement(-1, -1, -1);
    for (int i = 0; i < adjactive_matrix.size(); i++)
    {
        for (int k = 0; k < adjactive_matrix.size(); k++)
        {
            if (adjactive_matrix[i][k] == 0 && max_penalty->value < min_row_value[i] + min_column_values[k])
            {
                max_penalty->value = min_row_value[i] + min_column_values[k];
                max_penalty->column = k;
                max_penalty->row = i;
            }
        }
    }
    return max_penalty;
}

std::vector<std::vector<int>> delete_edges(std::vector<std::vector<int>> adjactive_matrix, MatrixElement *&max_penalty)
{
    adjactive_matrix[max_penalty->column][max_penalty->row] = -1;
    for (int i = 0; i < adjactive_matrix.size(); i++)
    {
        adjactive_matrix[max_penalty->row][i] = -1;
        adjactive_matrix[i][max_penalty->column] = -1;
    }
    return adjactive_matrix;
}

struct Edge
{
    int from;
    int to;
};

struct Result
{
    std::vector<Edge> edges;
    int penalty = 0;
};

Result prepare(std::vector<std::vector<int>> adjactive_matrix, Result result)
{
    std::vector<int> min_row_values = find_min_values(adjactive_matrix, true);
    subtract_min(adjactive_matrix, min_row_values, true);

    std::vector<int> min_column_values = find_min_values(adjactive_matrix, false);
    subtract_min(adjactive_matrix, min_column_values, false);

    int bound = std::accumulate(min_row_values.begin(), min_row_values.end(), 0) +
        std::accumulate(min_column_values.begin(), min_column_values.end(), 0);

    MatrixElement *max_penalty = calculate_max_penalty(adjactive_matrix, min_row_values, min_column_values);

    if (max_penalty->value == -1)
    {
        return;
    }
    Result new_result;
    std::vector<std::vector<int>> adjactive_matrix_with_delete_edges = delete_edges(adjactive_matrix, max_penalty);
    new_result.penalty = result.penalty + bound;
    new_result.edges = result.edges;
    Edge edge;
    edge.from = max_penalty->row;
    edge.to = max_penalty->column;
    new_result.edges.push_back(edge);
    Result result = prepare(adjactive_matrix_with_delete_edges, result);


}

int main()
{
    std::vector<std::vector<int>> adjactive_matrix = read_file("input/input.txt");
    println(adjactive_matrix);
    prepare(adjactive_matrix);
}

