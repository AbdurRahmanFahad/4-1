
vector<double> left_and_right_intersecting_points(Triangle tr, double py)
{
    vector<double> left_right_x, px;
    int j = 0;
    for (int i = 0; i <= 2; i++)
    {
        Point p0 = tr.points[i];
        Point p1 = tr.points[(i + 1) % 3];

        if (p0.y == p1.y)
            continue;

        double t = (py - p0.y) / (p1.y - p0.y);
        if (t < 0 || t > 1)
            continue;
        if (j < 2)
        {
            px.push_back(p0.x + t * (p1.x - p0.x));
            j++;
        }
    }
    sort(px.begin(), px.end());

    return px;
}

int x_to_column(double x)
{
    return round((x - leftx) / dx);
}

int y_to_row(double y)
{
    return round((topy - y) / dy);
}

double column_to_x(int c)
{
    return leftx + c * dx;
}

double row_to_y(int r)
{
    return topy - r * dy;
}

void apply_procedure()
{
    for (int i = 0; i < triangles.size(); i++)
    {
        double top_scanline = top_Scanline(triangles[i]);
        double bottom_scanline = bottom_Scanline(triangles[i]);
        double left_x, right_x;
        vector<double> plane = plane_equation(triangles[i]);

        //cout << "Triangle:"<<i<<"------------------\n";

        int r = y_to_row(bottom_scanline);
        int end_r = y_to_row(top_scanline);

        for (; r >= end_r; r--)
        {
            double j = row_to_y(r);
            vector<double> temp = left_and_right_intersecting_points(triangles[i], j);
            if (temp.size() < 2)
                continue;
            left_x = temp[0];
            right_x = temp[1];

            if (left_x < x_left_limit)
                left_x = x_left_limit;
            if (right_x > x_right_limit)
                right_x = x_right_limit;

            int c = x_to_column(left_x);
            int end_c = x_to_column(right_x);

            for (; c <= end_c; c++)
            {
                double k = column_to_x(c);

                double temp_z = get_z_value(k, j, plane);

                //int r = y_to_row(j);
                //int c = x_to_column(k);
                if (r < 0 || r >= screen_height || c < 0 || c >= screen_width)
                {
                    continue;
                }

                //printf("%d %d\n", r, c);

                if (temp_z < z_buffer[r][c] && temp_z >= z_front_limit)
                {
                    z_buffer[r][c] = temp_z;
                    frame_buffer[r][c] = triangles[i].color;
                }
            }
        }
    }
}

void free_memory()
{
    triangles.clear();
    for (int i = 0; i < screen_height; i++)
    {
        delete z_buffer[i];
        delete frame_buffer[i];
    }
    delete z_buffer;
    delete frame_buffer;
}

int main()
{
    read_data();
    initialize_z_buffer_and_frame_buffer();
    apply_procedure();
    save();
    free_memory();
}