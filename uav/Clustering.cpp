#include "clustering.h"

clustering::clustering(read_data& d) : d(d), no_of_addresses(d.no_of_addresses) 
{
	centroids.resize(this->k);
	no_of_points.resize(no_of_addresses); easting_sum.resize(no_of_addresses); northing_sum.resize(no_of_addresses);
	distances.resize(no_of_addresses);
};
clustering::~clustering() {};

clustering::clustering(int c_size)
{
	centroids.resize(c_size);
}

//Copy constructor
clustering::clustering(const clustering& cp) 
{
	centroids = cp.centroids;
}
void clustering::set_rand_centroids(int k_val) 
{
	default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
	uniform_int_distribution<int> randunit(1, no_of_addresses - 1);
	set<int> index_track;
	for (auto cluster_no = 0; cluster_no < k_val; cluster_no++) 
	{
		do 
		{
			idx = randunit(generator);
		} while (index_track.find(idx) != index_track.end()); //Ensuring idx is not already present in index_track
		index_track.insert(idx); 
		centroids[cluster_no] = d.data[idx]; //Making the random data point a centroid
		centroids[cluster_no].id = cluster_no; //Giving the random data point a unique id number
	}
}

void clustering::K_means(int k_val, vector<double>& distances) 
{
	double distance;
	distances.resize(no_of_addresses);
	for (auto adr_no = 0; adr_no < no_of_addresses; adr_no++) 
	{
		min_distance = DBL_MAX; // Assigning to maximum value to ensure if statement condition is true for first iteration of second for loop
		for (auto cluster_no = 0; cluster_no < k_val; cluster_no++) 
		{
			distance = std::sqrt(utility::length(d.data[adr_no], centroids[cluster_no]));// change this why??
			if (distance < min_distance) //Continually comparing distance between a single address and the centroids
			{ 
				min_distance = distance; //Set new min distance
				d.data[adr_no].id = centroids[cluster_no].id; //Setting id of address equal to id of centroid which has the small distance
			}

		}
		distances[adr_no] = min_distance; // do i need this yes i do ,, resize this! going to be huge as repeatedly called sort this out!!
	}
	//Intialising vectors required to recompute/improve centroids
	for (auto i = 0; i < no_of_addresses; i++) 
	{
		no_of_points[i] = 0;
		easting_sum[i] = 0;
		northing_sum[i] = 0;
	}
	int id_cluster;
	for (auto adr_no = 0; adr_no < no_of_addresses; adr_no++) 
	{
		id_cluster = d.data[adr_no].id;
		no_of_points[id_cluster] += 1;  //Adding +1 to count how many addresses are associated with each centroid
		easting_sum[id_cluster] += d.data[adr_no].x_coord; //Summing easting values of each address
		northing_sum[id_cluster] += d.data[adr_no].y_coord; //Summing northing values of each address
	}
	//Computing new x and y coordinates for each cluster by calculating mean value
	for (auto cluster_no = 0; cluster_no < k_val; cluster_no++) 
	{ 
		centroids[cluster_no].x_coord = easting_sum[cluster_no] / no_of_points[cluster_no]; 
		centroids[cluster_no].y_coord = northing_sum[cluster_no] / no_of_points[cluster_no];
	}
#ifdef TEST
	ofstream myfile;
	myfile.open("output_csv.txt");
	myfile << "x, y, id" << endl;

	for (auto i = 0; i < no_of_addresses; i++) {
		myfile << d.data[i].x_coord << "," << d.data[i].y_coord << "," << d.data[i].id << endl;
	}
	myfile.close();
	
#endif 
}

bool clustering::check_ids() 
{
	for (auto i : d.data) 
	{
		if (i.id == -1) { //If id = -1 the address id has not been correctly updated in K_means funciton 

			return false;
		}
	}
	return true;
}
bool clustering::stopping_condition(const vector<address_metadata>& obj, const vector<address_metadata>& obj2) 
{
	int cnt = 0;
	int cnt_to_match = obj.size();
	for (int i = 0; i < cnt_to_match; i++) 
	{
		if ((abs(obj[i].x_coord - obj2[i].x_coord) < 1e-5) && (abs(obj[i].y_coord - obj2[i].y_coord) < 1e-5)) //Checking coords are in range of tol
			cnt++;
	}
	if (cnt == cnt_to_match)
		return true;
	return false;
}
//operator !=(vector<address_metadata> const& obj, vector<address_metadata> const& obj2){
//	for (size_t i = 0; i < obj.size(); i++){
//		if ()
//	}
void clustering::coord_insert_sort(vector<address_metadata>& arg1) 
{
	int i = 1;
	int j;
	double temp_num1, temp_num2;
	address_metadata temp_obj;
	size_t rt_size = arg1.size();
	while (i < rt_size) 
	{
		temp_num1 = arg1[i].x_coord;
		temp_num2 = arg1[i].y_coord;
		temp_obj = arg1[i];
		j = i - 1;
		while (j >= 0 && (arg1[j].x_coord > temp_num1 && arg1[j].y_coord > temp_num2)) 
		{
			arg1[j + 1] = arg1[j];
			j--;
		}
		arg1[j + 1] = temp_obj;
		i++;
	}
}
bool clustering::check_distances(vector<double>& check_d_v, double max_dist) 
{
	max_dist *= 0.5;
	for (auto loc_distance : check_d_v)
		if (loc_distance > max_dist) //Distance between centroid and address greater than max distance of drone return false
			return false;
	return true;
}

void clustering::run_K_means() 
{

	bool in_range = false;
	bool converge;
	vector<double> distances_v;
	vector<address_metadata> track_centroids(2);
	while (!in_range)
	{ //continue all distances are within the flying distance
		converge = false;
		set_rand_centroids(k);
		while (!converge) 
		{ //continue until all centroids have converged
			track_centroids = centroids;
			K_means(k, distances_v);
			//coord_insert_sort(centroids); //Sorting by lowest x & y coordinates to prevent stopping_condition returning false when actually true
			//coord_insert_sort(track_centroids);
			if (stopping_condition(centroids, track_centroids)) //never met for large routes think of new way to overocme issue
			{ // strange bug where postcodes have same but swapped coordinates
				converge = true;
				if (check_distances(distances_v, 20)) //change this
				{ // change second param
					in_range = true;
					return;
				}
			}

		}
		k++; //Adding another cluster if conditions are not met
		centroids.resize(k);
		track_centroids.resize(k);

	}
}
//describe algorithms and also implmentation
// describing tests,, validation test cases
// actual results

void clustering::group_clusters()
{
	cluster_regions.resize(k);
	for (int i = 0; i < k; i++) 
	{//Initialising count values to 0
		id_index_count[i] = 0;
		id_count[i] = 0;
	}
	for (auto i : d.data) //Calculating number of addresses associated with each centroid
		id_count.at(i.id) += 1;

	for (int i = 0; i < k; i++)
		cluster_regions[i].resize(id_count.at(i)); // this line
	
	int idx = -1;
	for (int i = 0; i < d.data.size(); i++) 
	{
		// does this make sense?
		idx = d.data[i].id;
		cluster_regions[idx][id_index_count.at(idx)] = &d.data[i]; 
		id_index_count.at(d.data[i].id) += 1;
	} 

}

void clustering::add_depot(address_metadata dep)
{
	dep.depot = true;
	this->centroids.push_back(dep);
	this->centroids.insert(centroids.begin(), dep);
	
}

void clustering::add_depot()
{
	address_metadata default_dep;
	default_dep.x_coord = 0;
	default_dep.y_coord = 0;
	default_dep.depot = true;
}

void clustering::run_clustering(address_metadata dep)
{
	run_K_means();
	group_clusters();
}