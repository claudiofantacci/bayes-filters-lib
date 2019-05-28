# 📜 BayesFilters changelog

## 🔖 Version 0.9.100
##### `CMake`
- Minor version increases since API compatibility is broken.

##### `General improvements`
- Changed any::any default pointer value to nullptr.

##### `Filtering utilities`
- Constructor EstimatesExtraction::EstimatesExtraction() takes the state size, both linear and circular.
- Class EstimatesExtraction does not assume that the state is a 7-vector containing cartesian position and axis/angle representation of orientation anymore.
- Implemented MAP (maximum a posteriori) estimate extraction within method EstimatesExtraction::map().
- Implemented overloaded version of EstimatesExtraction::extract() taking extra arguments (particle weights at the previous time step, likelihoods at the current step and matrix of Markov transition probabilities between previous and current states) required to expose MAP extraction utiliy to the user.
- Implemented method GaussianMixture::resize().
- Implemented method Gaussian::resize().
- Implemented method ParticleSet::resize().
- Implemented evaluation of a multivariate Gaussian probability density function in method utils::multivariate_gaussian_density.
- Implemented evaluation of the logarithm of a multivariate Gaussian probability density function in method utils::multivariate_gaussian_log_density.
- Implemented evaluation of a multivariate Gaussian probability density function with UVR factorized covariance matrix in method `utils::multivariate_gaussian_density_UVR()`.
- Implemented evaluation of the logarithm of a multivariate Gaussian probability density function with UVR factorized covariance matrix in method `utils::multivariate_gaussian_log_density_UVR()`.
- Methods EstimatesExtraction::extract() return a std::pair containing a boolean indicating if the estimate is valid and the estracted estimate.
- Methods EstimatesExtraction::extract() assume that particle weights are in the log space.
- Constructor HistoryBuffer::HistoryBuffer() takes the state size.
- Renamed Logger::log_filenames() in Logger::log_file_names().
- Renamed Logger::get_prefix_path() in Logger::get_folder_path().
- Renamed Logger::get_prefix_name() in Logger::get_file_name_prefix().
- Logger::enable_log() now requires absolute or relative paths as input.
- utils.h is now a template header-only utility file.

##### `Filtering functions`
- Added pure public virtual method GaussianPrediction::getStateModel() (required to properly implement GPFPrediction::getStateModel()).
- Implemented method KFPrediction::getStateModel().
- Implemented method KFCorrection::getLikelihood().
- Implemented method UKFPrediction::getStateModel().
- Implemented method UKFCorrection::getLikelihood().
- Implemented method `SUKFCorrection::getLikelihood()`.
- Changed implementation of GaussianLikelihood::likelihood().
- Changed implementation of GPFPrediction::getStateModel().
- Changed implementation of GPFCorrection::getLikelihood().
- Changed implementation of GPFCorrection::evaluateProposal().
- Changed implementation of WhiteNoiseAcceleration::getTransitionProbability().
- Fixed missing const(s) keywords in signature of method StateModel::getTransitionProbability().
- Fixed missing const(s) keywords in signature of method WhiteNoiseAcceleration::getTransitionProbability().
- SUKFCorrection::getNoiseCovarianceMatrix() is now virtual.
- Removed decorator classes. Using decorator was an easy way of extending functionalities, but at the cost of writing erroneous behavior in the filters.

##### `Test`
- Mean extraction is performed using EstimatesExtraction utilities in test_UPF.
- Add mean extraction and logging in test_SIS to simplify inspection of the algorithm outcome.
- Reduce number of particles in test_SIS to reduce testing computation time in Debug.
- Add testUPF_MAP testing MAP (maximum a posteriori) estimate extraction within a UPF particle filter.
- Add `test_Gaussian_Density_UVR` testing the method `utils::multivariate_gaussian_density_UVR()`.
- Change test_Gaussian in order to test resizing.

## 🔖 Version 0.8.101
##### `Bugfix`
 - Add initial value to bool variable in UKFCorrection::correctStep().

##### `CMake`
 - Add CMake variable TEST_LOG_TO_FILE to disable file logs in tests.

##### `General improvements`
 - Added missing `override` keyword.
 - Reordered data member initialization list of SIS class.


## 🔖 Version 0.8.0

##### `Dependencies`
 - Removed OpenCV dependency.

##### `CMake`
 - Devel branch will now have +100 on the patch number to differentiate from master branch.
 - Fourth number of the project version has been removed to be compliant with SemVer system.
 - Third number of SemVer increases since API compatibility is broken.

#### `Data types`
 - Using only double data type within the whole library.

##### `Filtering algorithms`
 - Added logging capabilities to FilteringAlgorithm.
 - Removed SIS::setInitialization(), SIS::setPrediction(), SIS::setCorrection() and SIS:setResampling() methods. The associated unique_ptr classes are now mandatory arguments of ParticleFilter constructor.
 - Constructor SIS::SIS() takes the state size, both linear and circular, and the filtering step classes as arguments to initialize, respectively, the ParticleSet and the ParticleFilter classes.
 - Method SIS::filteringStep() uses VectorXi instead of VectorXf to represent particle parents.
 - Method SIS::filteringStep() uses particle weights in log space instead of linear space.
 - Moved default logging facilities of class SIS from method SIS::filteringStep() to overridden method Logger::log().
 - Re-implemented class KalmanFilter, a general Gaussian filtering algorithm using a GaussianPrediction and a GaussianCorrection.
 - Renamed class KalmanFilter to GaussianFilter.
 - Added call to virtual method Logger::log() in method GaussianFilter::filteringStep().

##### `Filtering functions`
 - Renamed UpdateParticles in BootstrapCorrection.
 - Removed VisualParticleFilter class.
 - Removed PFVisualCorrection and derived classes.
 - Added LikelihoodModel interface class.
 - Added GaussianLikelihood class.
 - Added class GaussianPrediction, a generic Gaussian prediction step.
 - Added class GaussianCorrection, a generic Gaussian correction step.
 - Added class KFPrediction, a (Gaussian) Kalman prediction step for LinearStateModel models.
 - Added class KFCorrection, a (Gaussian) Kalman correction step for LinearMeasurementModel models.
 - Added class UKFPrediction, a (Gaussian) unscented Kalman prediction step for StateModel and AdditiveStateModel models.
 - Added class UKFCorrection, a (Gaussian) unscented Kalman correction step for MeasurementModel and AdditiveMeasurementModel models.
 - Added class SUKFCorrection, a (Gaussian) unscented Kalman correction step for AdditiveMeasurementModel models.
 - Added class GPFPrediction, a particle filter prediction step that propagates the Gaussian belief associated to particles.
 - Added class GPFCorrection, a particle filter correction step that propagates the Gaussian belief associated to particles and weights them according to a Gaussian proposal distribution.
 - PFCorrection::getLikelihood() method is now pure virtual.
 - Used new ParticleSet class within classes PFPrediction, PFPredictionDecorator, PFCorrection, PFCorrectionDecorator, DrawParticles, BootstrapCorrection, Resampling, ResamplingWithPrior, ParticleSetInitialization, InitSurveillanceAreaGrid and SIS.
 - Method ResamplingWithPrior::resample() heavily changed (due to use of ParticleSet).
 - Methods Resampling::resample() and ResamplingWithPrior::resample() use VectorXi instead of VectorXf to represent particle parents.
 - Methods Resampling::resample() and Resampling::neff() uses particle weights in log space instead of linear space.
 - Methods ResamplingWithPrior::resample() uses particle weights in log space instead of linear space.
 - PFCorrection now performs measurements freeze before calling PFCorrection::correctStep() and does not call it if measurements freeze fails.
 - BootstrapCorrection::correctStep() now does not freeze measurements anymore.
 - BootstrapCorrection::correctStep() uses particle weights in log space instead of linear space.
 - InitSurveillanceAreaGrid::initialize() uses particle weights in log space instead of linear space.

##### `State models`
 - Added SimulatedStateModel class to simulate kinematic or dynamic models using StateModel classes.
 - Added non-pure virtual method StateModel::getTransitionProbability().
 - Added non-pure virtual method StateModel::getJacobian().
 - Added pure virtual method StateModel::getOutputSize().
 - Added pure virtual method ExogenousModel::getOutputSize().
 - Implemented method StateModelDecorator::getOutputSize().
 - Implemented AdditiveStateModel class inheriting from StateModel.
 - Implemented LinearStateModel class inheriting from AdditiveStateModel.
 - Implemented LTIStateModel class inheriting from LinearStateModel.
 - WhiteNoiseAcceleration class now inherits from LinearStateModel.
 - Implemented method WhiteNoiseAcceleration::getOutputSize().
 - Implemented method WhiteNoiseAcceleration::getTransitionProbability.

##### `Measurement models`
 - Added SimulatedLinearSensor class.
 - Added MeasurementModelDecorator class.
 - Added logging capabilities to MeasurementModel.
 - Removed method MeasurementModel::getNoiseSample().
 - Added pure virtual method MeasurementModel::getOutputSize().
 - Method MeasurementModel::measure() replaces method MeasurementModel::getAgentMeasurements() and does not take the state as input.
 - Method MeasurementModel::freezeMeasurements() replaces method MeasurementModel::bufferAgentData() const.
 - Method BootstrapCorrection::correctStep() uses MeasurementModel::freezeMeasurements().
 - Added class AdditiveMeasurementModel.
 - Added class LinearMeasurementModel.
 - Added class LTIMeasurementModel.
 - Renamed LinearSensor to LinearModel.
 - LinearModel class now inherits from LinearMeasurementModel.
 - LinearModel class now does not implement MeasurementModel::measure().

##### `Filtering utilities`
 - Added Data class in order to have a type for encapsulating data coming from any process.
 - Added GaussianMixture, Gaussian and ParticleSet classes.
 - Added directional_add(), directional_sub() and directional_mean() functions in directional_statistics.h/cpp.
 - Added sigma_point(), unscented_weights() and unscented_transform() functions in sigma_point.h/cpp.
 - Added UTWeight struct to store unscented transform weights in sigma_point.h/cpp.
 - Added alias FunctionEvaluation in sigma_point.h/cpp.
 - Added method utils::log_sum_exp() to evaluate the logarithm of a sum of exponentials.

##### `Test`
 - Removed test_ParticleFilter.
 - Added test_DirectionalStatisticsUtils for directional_statistics.h/cpp.
 - Added test_SigmaPointUtils for sigma_point.h/cpp.
 - Added test_Gaussian for Gaussian and GaussianMixture classes.
 - Added test_KF testing Gaussian filtering with KFPrediction and KFCorrection.
 - Added test_UKF testing Gaussian filtering with UKFPrediction and UKFCorrection.
 - Added test_mixed_KF_UKF testing Gaussian filtering with KFPrediction and UKFCorrection.
 - Added test_mixed_UKF_KF testing Gaussian filtering with UKFPrediction and KFCorrection.
 - Added test_mixed_KF_SUKF testing Gaussian filtering with KFPrediction and SUKFCorrection.
 - Added test_UPF testing particle filtering with UKFPrediction and UKFCorrection.
 - Updated test_SIS.
 - Updated test_SIS_Decorators.


## 🔖 Version 0.7.1.0
##### `Bugfix`
 - Fixed WhiteNoiseAcceleration implementation.


## 🔖 Version 0.7.0.0
##### `Filtering classes`
 - Removed PFVisualCorrection::getVisualObservationModel() and PFVisualCorrection::setVisualObservationModel().

##### `Bugfix`
 - Fixed PF prediction and correction move constructor (minor fix).

##### `CMake`
 - Threads is now a dependency of the exported library. This will solve a CMake error during configuration in CMake projects linking BayesFilters.
 - BayesFilters is now fully relocatable.


## 🔖 Version 0.6.2.0
##### `Filtering classes`
 - Added ResamplingWithPrior class.
 - Added HistoryBuffer and EstimatesExtraction classes.

##### `Filtering features`
 - Added 'all' option to skip() method of particle filters. This option is particularly useful to reset the internal status of the filters.

##### `Dependencies`
 - Removed Eigen::NullaryExpr() calls. Now the library can be compiled with any Eigen 3.3 version.

##### `Bugfix`
 - Windows is now fully supported and tested.

##### `Test`
 - Added Appveyor and Travis yml files. Tests still need to be improved.

##### `CMake`
 - Updated CMake modules.


## 🔖 Version 0.6.1.0
##### `CMake`
 - Updated installation helper files, which are updated from YCM commit f162fcb.


## 🔖 Version 0.6.0.1
##### `Filtering classes`
 - Fixed FilteringAlgorithm::filteringRecursion() the invocation position of initialization.

## 🔖 Version 0.6.0.0
 - This is the first public release of the BayesFilters library 🎉.
