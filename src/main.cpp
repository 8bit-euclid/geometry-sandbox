#include <iostream>
#include <Eigen/Dense>
#include <igl/doublearea.h>
#include <igl/volume.h>
#include "triangle.h"

void test_eigen() 
{
    std::cout << "Testing Eigen..." << std::endl;

    // Create a 3x3 matrix
    Eigen::Matrix3d mat;
    mat << 1, 2, 3,
           4, 5, 6,
           7, 8, 9;

    // Print the matrix
    std::cout << "Matrix A:\n" << mat << std::endl;

    // Create a vector
    Eigen::Vector3d vec(1, 2, 3);
    std::cout << "Vector b:\n" << vec << std::endl;

    // Perform matrix-vector multiplication
    Eigen::Vector3d result = mat * vec;
    std::cout << "A * b =\n" << result << std::endl;

    // Calculate the determinant
    double det = mat.determinant();
    std::cout << "Determinant of A: " << det << std::endl;

    // Calculate the transpose
    Eigen::Matrix3d transposed = mat.transpose();
    std::cout << "Transpose of A:\n" << transposed << std::endl;
}

void test_libigl() 
{
    std::cout << "\nTesting LibIGL..." << std::endl;

    // Create a simple triangle mesh (tetrahedron)
    // Define vertices of a tetrahedron
    Eigen::MatrixXd V(4, 3);
    V << 0.0, 0.0, 0.0,
         1.0, 0.0, 0.0,
         0.5, 0.866, 0.0,
         0.5, 0.289, 0.816;

    // Define faces of the tetrahedron
    Eigen::MatrixXi F(4, 3);
    F << 0, 1, 2,
         0, 1, 3,
         1, 2, 3,
         0, 2, 3;

    std::cout << "Created a tetrahedron mesh:" << std::endl;
    std::cout << "Number of vertices: " << V.rows() << std::endl;
    std::cout << "Number of faces: " << F.rows() << std::endl;
    
    // Use LibIGL function to compute face areas
    Eigen::VectorXd dblA;
    igl::doublearea(V, F, dblA);
    
    std::cout << "Face areas (using LibIGL doublearea):" << std::endl;
    for (int i = 0; i < dblA.rows(); ++i) {
        std::cout << "Face " << i << ": " << dblA(i) / 2.0 << std::endl;
    }
    
    std::cout << "Total surface area (using LibIGL): " << dblA.sum() / 2.0 << std::endl;

    // Use LibIGL function to compute mesh volume
    Eigen::VectorXd vol;
    igl::volume(V, F, vol);
    double total_volume = vol.sum();
    
    std::cout << "Mesh volume (using LibIGL): " << total_volume << std::endl;
    std::cout << "LibIGL test completed successfully!" << std::endl;
}

static void test_triangle()
{
    std::cout << "\nTesting Triangle..." << std::endl;
    
    struct triangulateio in; memset(&in, 0, sizeof(in));
    struct triangulateio out; memset(&out, 0, sizeof(out));

    in.numberofpoints = 4;
    in.pointlist = (TRI_REAL*) malloc(in.numberofpoints * 2 * sizeof(TRI_REAL));
    // Square points (counter-clockwise)
    in.pointlist[0] = 0.0; in.pointlist[1] = 0.0;
    in.pointlist[2] = 1.0; in.pointlist[3] = 0.0;
    in.pointlist[4] = 1.0; in.pointlist[5] = 1.0;
    in.pointlist[6] = 0.0; in.pointlist[7] = 1.0;

    // Segments (edges of square)
    in.numberofsegments = 4;
    in.segmentlist = (int*) malloc(in.numberofsegments * 2 * sizeof(int));
    int segs[8] = {0,1, 1,2, 2,3, 3,0};
    for (int i = 0; i < 8; ++i) in.segmentlist[i] = segs[i];

    // Perform triangulation (p = PSLG, q = quality)
    triangulate(const_cast<char*>("pq"), &in, &out, nullptr);
    std::cout << "Triangle produced " << out.numberoftriangles
              << " triangles from square." << std::endl;

    // Clean up
    free(in.pointlist); free(in.segmentlist);
    free(out.pointlist); free(out.trianglelist); free(out.segmentlist); free(out.edgelist);
    std::cout << "Triangle test completed." << std::endl;
}

int main() {
    test_eigen();
    test_libigl();
    test_triangle();
    return 0;
}
