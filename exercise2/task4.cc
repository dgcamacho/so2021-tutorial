#include<iostream>
#include<ctime>
#include<cstdlib>
#include<span>
#include<cassert>
#include<math.h>

using T= double;
using DynamicVector= std::span<T, std::dynamic_extent>;
void init(double* Mat, int const nrows, int const ncols, T const val)
{
    for(int i = 0; i< nrows; i++)
        for(int j = 0; j<ncols; j++)
            Mat[i*ncols+j]= val;
    
}

void init(double* Mat, int const nrows, int const ncols)
{
    for(int i = 0; i< nrows; i++)
    {   
        std::cout<<"enter the elements of row "<<i<<std::endl;
        for(int j = 0; j<ncols; j++)
        {   
            std::cin>>Mat[i*ncols+j];
        }   
        std::cout<<std::endl;
    } 
}



double& access(double* Mat, int const nrows, int const ncols, int const i, int const j)
{
    return Mat[i*ncols+j];
}


void print(DynamicVector Vect)
{
    std::cout<<"printing the vector"<<std::endl;
    for(int i = 0; i< Vect.size(); i++)
        {
            std::cout<<Vect[i]<<"\t";
        }
    std::cout<<std::endl;
}

void print(double* Mat, int const nrows, int const ncols)
{
    for(int i = 0; i< nrows; i++)
        {
            for(int j = 0; j<ncols; j++)
                std::cout<<Mat[i*ncols+j]<<"\t";
            std::cout<<std::endl;
        }
}

void scale(DynamicVector Vect, double const val)
{
    for(int i = 0; i< Vect.size(); i++)
    {
        Vect[i]*=val;
    }
}

void add(DynamicVector Vect1, DynamicVector Vect2, DynamicVector Vect_out)
{
    assert(Vect1.size() == Vect2.size());
    assert(Vect1.size() == Vect_out.size());
    for (int i=0; i<Vect1.size();i++)
    {
        Vect_out[i]= Vect1[i]+Vect2[i];
    }
}

void dot(DynamicVector Vect1, DynamicVector Vect2, T& dot_product)
{
    assert(Vect1.size()==Vect2.size());
    dot_product=0;        
    for(int i=0; i<Vect1.size(); i++)
    {
        dot_product+= Vect1[i]*Vect2[i];
    }
}
void dot(double* Mat, DynamicVector Vect_in, DynamicVector Vect_out, int const nrows, int const ncols)
{   
    assert(nrows==Vect_out.size());
    assert(ncols==Vect_in.size());

    double sum;
    for(int i=0; i<nrows; i++)
    {   
        sum=0;
        for(int j=0; j<ncols; j++)
        {
            sum+= access(Mat, nrows, ncols, i, j)*Vect_in[j];
        }
        Vect_out[i]= sum;
    }
}

void randInit(DynamicVector Vect)
{   
    double max;
    std::cout<<"Enter the Max val"<<std::endl;
    std::cin>>max;
    std::srand(std::time(nullptr));
    for(int i=0; i< Vect.size(); i++)
        Vect[i]= 1+ std::rand()/(RAND_MAX+1.0)*max;
    print(Vect);
}


void rayleigh_quotient(double* Mat, DynamicVector r, int const nrows, int const ncols, double& r_quotient)
{
    auto A_r= r;    double dot_product;

    dot(Mat, r, A_r, nrows, ncols);
    dot(r,A_r, r_quotient);
    dot(r,r,dot_product);
    r_quotient/= dot_product;
    
} 

void power_method(double* Mat, DynamicVector r, int const nrows, int const ncols, int const niterations, double& r_quotient)
{
    double dot_product;
    for(int i=0; i< niterations; i++)
    {
        dot(Mat, r, r, nrows, ncols);
        dot(r, r, dot_product);
        dot_product= std::sqrt(dot_product);
        assert(dot_product!=0.0);
        scale(r, 1/dot_product);
        print(r);
        rayleigh_quotient(Mat, r, nrows, ncols, r_quotient);
        std::cout<<"Rayleigh Quotient:"<<r_quotient<<std::endl;
    }
    
}

double test(double* Mat, DynamicVector r, int const nrows, int const ncols, double const r_quotient)
{   
    auto A_r= r;    double dot_product;
    dot(Mat, r, A_r, nrows, ncols);
    scale(r, -r_quotient);
    add(A_r, r, r);
    dot(r,r, dot_product);
    dot_product= std::sqrt(dot_product);

    return dot_product;
}
int main()
{
    int nrows=3, ncols=3; // Symmetric and Positive Definite
    double* Mat1= new double[nrows*nrows] {3,0,0,0,1,0,0,0,1};
    double* Mat2= new double[nrows*nrows] {4,-1,-1,0.5,2,-1,0,0,1};
    int niterations= 20;    double r_quotient;
    
    // init(Mat, nrows, ncols);
    //access(Mat, nrows, ncols, 1,1);
    print(Mat1, nrows, ncols);
    
    double* data_= new double[nrows];
    
    auto r= DynamicVector(data_, nrows);

    randInit(r);

    power_method(Mat1, r, nrows, ncols, niterations, r_quotient);
    auto error= test(Mat1, r, nrows, ncols, r_quotient);
    std::cout<<"Error: "<<error<<std::endl;

    return 0;
}
