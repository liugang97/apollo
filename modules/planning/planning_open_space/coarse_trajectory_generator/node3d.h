/******************************************************************************
 * Copyright 2018 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

/*
* @file
*/

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "modules/common_msgs/config_msgs/vehicle_config.pb.h"
#include "modules/planning/planning_open_space/proto/planner_open_space_config.pb.h"

#include "modules/common/math/box2d.h"

namespace apollo {
namespace planning {

class Node3d {
 public:
  Node3d(const double x, const double y, const double phi);
  Node3d(const double x,
          const double y,
          const double phi,
          const std::vector<double>& XYbounds,
          const PlannerOpenSpaceConfig& open_space_conf);
  Node3d(const std::vector<double>& traversed_x,
          const std::vector<double>& traversed_y,
          const std::vector<double>& traversed_phi,
          const std::vector<double>& XYbounds,
          const PlannerOpenSpaceConfig& open_space_conf);
  virtual ~Node3d() = default;
  static apollo::common::math::Box2d GetBoundingBox(
          const common::VehicleParam& vehicle_param_,
          const double x,
          const double y,
          const double phi);
  double GetCost() const {
      return traj_cost_ + heuristic_cost_;
  }
  double GetTrajCost() const {
      return traj_cost_;
  }
  double GetHeuCost() const {
      return heuristic_cost_;
  }
  int GetGridX() const {
      return x_grid_;
  }
  int GetGridY() const {
      return y_grid_;
  }
  double GetX() const {
      return x_;
  }
  double GetY() const {
      return y_;
  }
  double GetPhi() const {
      return phi_;
  }
  bool operator==(const Node3d& right) const;
  const std::string& GetIndex() const {
      return index_;
  }
  size_t GetStepSize() const {
      return step_size_;
  }
  bool GetDirec() const {
      return direction_;
  }
  double GetSteer() const {
      return steering_;
  }
  std::shared_ptr<Node3d> GetPreNode() const {
      return pre_node_;
  }
  const std::vector<double>& GetXs() const {
      return traversed_x_;
  }
  const std::vector<double>& GetYs() const {
      return traversed_y_;
  }
  const std::vector<double>& GetPhis() const {
      return traversed_phi_;
  }
  const double& GetTravelDist() const {
      return travel_distance_;
  }
  void SetPre(std::shared_ptr<Node3d> pre_node) {
      pre_node_ = pre_node;
  }
  void SetDirec(bool direction) {
      direction_ = direction;
  }
  void SetTrajCost(double cost) {
      traj_cost_ = cost;
  }
  void SetHeuCost(double cost) {
      heuristic_cost_ = cost;
  }
  void SetSteer(double steering) {
      steering_ = steering;
  }
  void SetTravelDist(double dist) {
      travel_distance_ = dist;
  }

 private:
  static std::string ComputeStringIndex(
          int x_grid, int y_grid, int phi_grid);

 private:
  double x_ = 0.0;
  double y_ = 0.0;
  double phi_ = 0.0;
  size_t step_size_ = 1;  // 当前节点经过的点的步数，即 traversed_x_ 的个数
  std::vector<double> traversed_x_;
  std::vector<double> traversed_y_;
  std::vector<double> traversed_phi_;
  int x_grid_ = 0;    // 当前节点在栅格地图中的x坐标
  int y_grid_ = 0;    // 当前节点在栅格地图中的y坐标
  int phi_grid_ = 0;    // 当前节点在栅格地图中的phi坐标
  std::string index_;    // 当前节点的索引
  double traj_cost_ = 0.0;  // 当前节点的轨迹代价，即 f = g + h 中的 g
  double heuristic_cost_ = 0.0;  // 启发代价，即 h
  double cost_ = 0.0;
  std::shared_ptr<Node3d> pre_node_ = nullptr;
  double steering_ = 0.0;
  // true for moving forward and false for moving backward
  bool direction_ = true;
  // travel distance in direction_
  double travel_distance_ = 0.0;

  // park generic
 public:
  Node3d(const double x,
          const double y,
          const double phi,
          const std::vector<double>& XYbounds,
          const WarmStartConfig& warm_start_conf);

  Node3d(const std::vector<double>& traversed_x,
          const std::vector<double>& traversed_y,
          const std::vector<double>& traversed_phi,
          const std::vector<double>& XYbounds,
          const WarmStartConfig& warm_start_conf);
};

}  // namespace planning
}  // namespace apollo
