#ifndef TetheredDiffusionModel_H
#define TetheredDiffusionModel_H

#include "IMotionModel.h"
#include "../DataManager/DataManager.h"
#include <vector>
#include <boost/random/mersenne_twister.hpp>
#include <iostream>

class TetheredDiffusionModel : public IMotionModel {

private:
	double _diffCoeff; // diffusion coefficient
	double _stiffCoeff; // stiffness coefficient
	double _dt; // sampling interval
	DataManager::AxisEnum _axis; // axis to which this model is associated
	DataManager* _dm; // reference to the data manager
	boost::random::mt19937 gen; // Mersenne Twister random number generator
	double CalculateDiffusionCoefficient(const std::vector<std::vector<double> >&);
	double CalculateStiffnessCoefficient(const std::vector<std::vector<double> >&);
	void print(std::ostream&) const;
public:
	TetheredDiffusionModel () :
		IMotionModel(),
		_diffCoeff(0),
		_stiffCoeff(0),
		_dt(0),
		_axis(DataManager::X) // default to the X axis
		 {
			gen.seed(0); // by default set seed to zero
		};
		
	TetheredDiffusionModel
		(const double& dt, 
			const double& diffCoeff, 
			const double& stiffCoeff,
			const DataManager::AxisEnum& axis,
			const unsigned int& seed = 0) : 
		IMotionModel(),
		_diffCoeff(diffCoeff),
		_stiffCoeff(stiffCoeff),
		_dt(dt),
		_axis(axis) {
			gen.seed(seed); // set the RNG seed
		};
	
	double Evaluate(const double&, const double&) const;
	double Sample(const double&);
	void UpdateParameters();
	
	void SetDataManager(DataManager* dm) { _dm = dm; }

};

#endif