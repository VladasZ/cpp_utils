//
//  NewPath.hpp
//  cpp_tools
//
//  Created by Vladas Zakrevskis on 03/08/20.
//  Copyright © 2017 VladasZ. All rights reserved.
//

#pragma once


#include <vector>
#include <boost/filesystem.hpp>


namespace cu {

	namespace fs = boost::filesystem;

	using paths = std::vector<fs::path>;

	class NewPath {

	public:

		static paths ls(const std::string& = ".");
		static fs::path pwd();

	};

}
