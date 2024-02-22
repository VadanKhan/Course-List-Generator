#include <algorithm> // for std::sort
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

std::string DEFAULT_FILENAME = "courselist.dat";

// Structure to hold course data in a convenient / readable way.
struct Course
{
  double score;
  int id;
  std::string name;
};

// Function to read data from file
// This is C and so need to define what you are going to return when defining a function.
std::vector<Course> read_data(const std::string &filename)
{
  std::vector<Course> courses;
  std::ifstream file(filename);
  if (!file)
  {
    std::cerr << "Unable to open file: " << filename << std::endl;
    return courses;
  }

  while (!file.eof())
  {
    Course course;
    file >> course.score >> course.id;
    /*This line reads the score and id of the course from the file. It expects the score and id to
    be separated by whitespace (such as a space or a newline). */
    std::getline(file >> std::ws, course.name);
    /*This line reads the rest of the line from the file into course.name. This is done because
    the name of the course may contain spaces. Uses std::ws to remove whitespaces*/
    if (file)
    { // Check if read was successful
      courses.push_back(course);
    }
  }

  file.close();
  return courses;
}

std::tuple<double, double, double> calculate_mean_and_std_dev(const std::vector<double> &values)
{
  double mean = std::accumulate(values.begin(), values.end(), 0.0) / values.size();
  double sq_sum = 0.0;
  for (double value : values)
  {
    double diff = value - mean;
    sq_sum += std::pow(diff, 2); // equivalent to std::pow(diff, 2)
  }
  int degrees_of_freedom{
      1}; // establish the statisical adjustment for population standard deviation
  double stddev = std::sqrt(sq_sum / (values.size() - degrees_of_freedom));
  double mean_stddev = stddev / std::sqrt(values.size());
  return std::make_tuple(mean, stddev, mean_stddev);
}

bool compareByID(const Course &a, const Course &b)
// Comparator for sorting by ID
{
  return a.id < b.id;
}

bool compareByName(const Course &a, const Course &b)
// Comparator for sorting by name
{
  return a.name < b.name;
}

std::tuple<std::vector<std::string>, double, double, double> course_list_generator(const std::vector<int> &vec1,
                                                                                   const std::vector<std::string> &vec2,
                                                                                   const std::vector<double> &scores,
                                                                                   int first_digit,
                                                                                   const std::string &sort_by)
{
  std::vector<Course> filtered_courses;
  std::vector<double> filtered_scores;
  for (size_t i = 0; i < vec1.size() && i < vec2.size() && i < scores.size(); ++i)
  {
    // Check if the first digit of vec1[i] matches the input value
    int first_digit_of_id = vec1[i];
    while (first_digit_of_id >= 10)
      first_digit_of_id /= 10;

    if (first_digit == 0 || first_digit_of_id == first_digit)
    {
      Course course;
      course.id = vec1[i];
      course.name = vec2[i];
      course.score = scores[i];
      filtered_courses.push_back(course);
      filtered_scores.push_back(scores[i]);
    }
  }

  // Sort the courses based on the sort_by parameter
  if (sort_by == "id")
  {
    std::sort(filtered_courses.begin(), filtered_courses.end(), compareByID);
  }
  else if (sort_by == "name")
  {
    std::sort(filtered_courses.begin(), filtered_courses.end(), compareByName);
  }

  // Convert the sorted courses to a vector of strings
  std::vector<std::string> course_list;
  for (const Course &course : filtered_courses)
  {
    std::stringstream string;
    string << "PHYS " << course.id << " " << course.name;
    course_list.push_back(string.str());
  }

  // Calculate the mean, standard deviation, and mean standard deviation of the scores
  double mean, stddev, mean_stddev;
  std::tie(mean, stddev, mean_stddev) = calculate_mean_and_std_dev(filtered_scores);

  return std::make_tuple(course_list, mean, stddev, mean_stddev);
}

std::tuple<std::string, std::string, int> get_user_inputs() {
  // Get inputs from the user
  std::string datafile;
  std::string sort_specifier;
  int course_specifier;
  std::cout << "You can specify the name of the datafile to extract. If you want to use the default datafile 'courselist.dat', enter '-d'.\n"
            "You can also sort output data by course 'id' or course 'name'. Additionally, you can specify to print all courses '0' or to print courses of a specific level ('1', '2', '3', '4').\n";
  do
  {
    std::cout << "Enter the name of the datafile (or '-d' for default), 'id' or 'name', and an integer (0, 1, 2, 3, or 4) in one line (using spaces): ";
    std::cin >> datafile >> sort_specifier >> course_specifier;
    if (datafile == "-d") {
      datafile = DEFAULT_FILENAME;
    }
    if (std::cin.fail())
    {
      std::cin.clear();                                                   // clear the error state
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // remove the invalid input
      std::cout << "Invalid input. Please enter the name of the datafile (or '-d' for default), 'id' or 'name' for the first input and an integer"
                  "(0, 1, 2, 3, or 4) for the second input.\n";
    }
    else if (sort_specifier != "id" && sort_specifier != "name")
    {
      std::cout << "Invalid input. The second input must be either 'id' or 'name'.\n";
    }
    else if (course_specifier < 0 || course_specifier > 4)
    {
      std::cout << "Invalid input. The third input must be an integer between 0 and 4.\n";
    }
  } while (std::cin.fail() || (sort_specifier != "id" && sort_specifier != "name") || (course_specifier < 0 || course_specifier > 4));

  return std::make_tuple(datafile, sort_specifier, course_specifier);
}



int main()
{
  std::tuple<std::string, std::string, int> inputs = get_user_inputs();

  // Access the outputs
  std::string data_file = std::get<0>(inputs);
  std::string sort_specifier = std::get<1>(inputs);
  int course_specifier = std::get<2>(inputs);

  data_file = "courselist.dat";

  // Read data from file
  std::vector<Course> courses = read_data(data_file);

  std::cout << "-----------------------" << std::endl;

  // Print number of courses read
  std::cout << "Number of courses read: " << courses.size() << std::endl;

  // Print a separator
  std::cout << "-----------------------" << std::endl;

  // Create separate vectors for scores, ids, and names
  std::vector<double> scores;
  std::vector<int> ids;
  std::vector<std::string> names;

  // Iterate over the courses vector
  for (const Course &course : courses)
  {
    // Push each attribute into the corresponding vector
    scores.push_back(course.score);
    ids.push_back(course.id);
    names.push_back(course.name);
  }

  // Generalte the list of courses
  std::tuple<std::vector<std::string>, double, double, double> result = course_list_generator(ids, names, scores, course_specifier, sort_specifier);

  // access the outputs
  std::vector<std::string> course_list = std::get<0>(result);
  double mean{std::get<1>(result)};
  double population_error{std::get<3>(result)};

  // Print the course list
  for (const auto &course : course_list)
  {
    std::cout << course << std::endl;
  }

  // Print a separator
  std::cout << "-----------------------" << std::endl;

  // Print the stats of the selection
  std::cout << "Mean of the marks for selection: " << mean << std::endl;
  std::cout << "Population Error of the marks for selection: " << population_error << std::endl;

  std::cout << "-----------------------" << std::endl;
  return 0;
}
