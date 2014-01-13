#!/usr/bin/env ruby

# NEIGHBOR JOINING ALGORITHM

# parses input file or stdin
# checks if the node number is valid
# checks compatibility of node number and lines
# stores input in 2-dimensional array (matrix)
# first row and first number of the matrix
# hold node indices (because of further matrix transformations)
# returns distance matrix with one additional row and column
def parse_input(input)
  lines = input.lines.map(&:chomp)
  $n = lines.shift.to_i
  if $n <= 0
    abort "ERROR: Wrong node number: #{$n}"
  end
  number_of_lines = $n*($n-1)/2
  if $n*($n-1)/2 != lines.size
    abort "ERROR: Wrong number of lines: #{lines.size} for #{$n} nodes, should be #{number_of_lines}"
  end
  matrix = Array.new($n+1) { Array.new($n+1) { 0  } }
  matrix[0] = [0] + (0...$n).to_a

  for i in 0...$n
    matrix[i+1][0] = i
  end

  lines.each do |line|
    tmp = line.split(" ").map{ |q| q.to_f }
    matrix[tmp[0]+1][tmp[1]+1] = tmp[2]
    matrix[tmp[1]+1][tmp[0]+1] = tmp[2]
  end
  matrix
end


# prints matrix
def print_matrix(matrix)
  matrix.each do |m|
    print m
    puts
  end
end


# returns sum of elements in i-th row 
def get_sum(matrix, i)
  sum_ = 0
  for k in 1...matrix.length
    sum_ +=  matrix[i][k]
  end
  sum_
end


# calculates Q matrix for a given distance_matrix
# it operates on the upper part of the matrix (symmetry)
# skips first row and first column (indexes)
# returns Q matrix
def calc_matrix_q(distance_matrix)
  m = Marshal.load(Marshal.dump(distance_matrix))
  sums = Array.new( distance_matrix.length ) { 0 }
  for i in 1...sums.length
    sums[i] = get_sum(distance_matrix, i)
  end 
  const = $r - 2
  for i in 1...distance_matrix.length
    for j in i+1...distance_matrix.length
      m[i][j] = const * distance_matrix[i][j] - sums[i] - sums[j]
      m[j][i] = m[i][j]
    end
  end
  m
end


# searches for the smallest value
# skips diagonal elements
# returns matrix indices for the minimum value
def find_min_elem(matrix)
  min = matrix[1][2]
  indices = [1, 2] 
  for i in 1...matrix.length
    for j in i+1...matrix.length
      if ( matrix[i][j] < min )
        min = matrix[i][j]
        indices = [i, j]
      end
    end
  end
  indices
end


# calculates distances for nodes i, j
# to the new node
# returns distance values for 
def distance_members(matrix, i, j)
  distances = []
  distances[0] = matrix[i][j] / 2.to_f + (get_sum(matrix, i) - get_sum(matrix, j)) / (2.to_f * ($r - 2))
  distances[1] = matrix[i][j] - distances[0]
  distances
end


# calculates distances for the non-i and non-j
# nodes, returns array of distances
def distance_others(distance_matrix, i, j)
  distances = []
  for k in 1...distance_matrix.length
    next if k == i || k == j
    distances.push((distance_matrix[i][k] + distance_matrix[j][k] - distance_matrix[i][j]) / 2.to_f)
  end
  distances
end

# deletes rows i and j
# deletes columns i and j
# returns reduced matrix
def reduce_matrix(distance_matrix, i, j)
  distance_matrix[i] = nil
  distance_matrix[j] = nil
  distance_matrix.compact!
  distance_matrix.map{ |q| q[i] = nil if q }
  distance_matrix.map{ |q| q[j] = nil if q }
  distance_matrix.map{ |q| q.compact! }
  distance_matrix
end

# updates distance matrix with 
# distances of the remaining nodes to the new node
# returns updated distance matrix
def add_node_to_distance_matrix(distance_matrix, distances)
  n = distance_matrix.length
  row = Array.new(n) { 0 }
  row[0] = $n
  distance_matrix.first.push($n)
  for i in 1...n
      row[i] = distances.shift
      distance_matrix[i].push(row[i])
  end 
  distance_matrix.push(row + [0] )
  distance_matrix
end


# main program
# initialize
input = $<.read
$n = 0
distance_matrix = parse_input(input)
tree =  []
$r = distance_matrix.length-1
iter = distance_matrix.length-4


for l in 0...iter
  q_matrix = calc_matrix_q(distance_matrix)

  i, j = find_min_elem(q_matrix)
  members = distance_members(distance_matrix, i, j)
  tree.push([distance_matrix[0][i], $n, members[0]].join(" "))
  tree.push([distance_matrix[0][j], $n, members[1]].join(" "))
  others = distance_others(distance_matrix, i, j)

  distance_matrix = reduce_matrix(distance_matrix, i, j)
  distance_matrix = add_node_to_distance_matrix(distance_matrix, others)
  $n += 1
  $r -= 1
end

# joining the last three nodes with a new node

h = distance_matrix

first = ( h[1][2] + h[1][3] - h[2][3] ) / 2.to_f
second = ( h[2][1] + h[2][3] - h[1][3]) / 2.to_f
third = ( h[2][3] + h[1][3] - h[1][2] ) / 2.to_f

tree.push("#{h[0][1]} #{$n} #{first}")
tree.push("#{h[0][2]} #{$n} #{second}")
tree.push("#{h[0][3]} #{$n} #{third}")

puts tree