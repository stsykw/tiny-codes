/* -*- mode: c++; coding: utf-8-unix; -*- 
 * graph-test.cc
 * Created by Satoshi Yukawa on 26 July 2017.
 * Copyright 2017 Satoshi Yukawa. All rights reserved. 
 */


#include <iostream>
/*
  boost libraryをつかう
   http://www.boost.org/ のboost libraryが必要
 */
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>

int main(int argc, char* argv[]){
  // 宣言
  //typedef boost::adjacency_list<boost::vecS,boost::listS,boost::undirectedS> Graph;
  typedef boost::adjacency_list<boost::vecS,boost::vecS,boost::undirectedS> Graph;
  Graph G;
  int num=6;
  int component[num];


  // 初期化
  for(int i=0;i<num;i++){
    component[i] = 0;
  }
  // edgeをgraphに追加。
  boost::add_edge(0,1,G); // 0と1がつながってる
  boost::add_edge(0,2,G); // 0と1がつながってる
  boost::add_edge(0,3,G); // 0と1がつながってる
  boost::add_edge(0,4,G); // 0と1がつながってる
  boost::add_edge(0,5,G); // 0と1がつながってる
  boost::add_edge(2,4,G); // 2と4がつながってる
  boost::add_edge(1,4,G); // 1と4がつながってる
  boost::add_edge(1,2,G); // 1と4がつながってる
  boost::add_edge(2,5,G); // 1と4がつながってる
  boost::add_edge(2,3,G); // 1と4がつながってる
  boost::add_edge(4,3,G); // 1と4がつながってる
  boost::add_edge(4,5,G); // 1と4がつながってる
  
  // 全vertex数の出力
  std::cout << "total vertex " << boost::num_vertices(G) << "\n";
  
  // つながり具合の解析
  int cluster = boost::connected_components(G,&component[0]);
  std::cout << "# of clusters " << cluster << '\n'; // クラスター数
  for(int i=0;i<boost::num_vertices(G);i++){
    std::cout << i << " " << component[i] << '\n'; 
  }

// clear vertex 0  
  boost::clear_vertex(0,G);
  /*
 ここでつかってるVertexList(テンプレート二つ目)をvecSで持つタイプだと、頂点を削除すると、
 頂点番号が前に詰められるので、あとの番号と実際の頂点との対応関係が不明になる。
 上記、clear_vertexは、繋がっているedgeが消されるので、一見目的に合致しているように見えるが、
 削除できないので、孤立したvertexが残り、「物理的に繋がっていないボンド」と
   「切れてしまったボンド」の区別ができない。
   孤立vertex(今使いたいモデルではボンド)を生死で区別するためには、
   別の物理量を見ないといけない。
   
   
   VertexListをlistSで持つとすると、数字を直接入れてadd_edgeできない。
   http://d.hatena.ne.jp/eagle_raptor/20111221/1324478088
   
     */
//  boost::remove_vertex(0,G);

    // 全vertex数の出力
  std::cout << "total vertex " << boost::num_vertices(G) << "\n";

  // つながり具合の解析
  cluster = boost::connected_components(G,&component[0]);
  std::cout << "# of clusters " << cluster << '\n'; // クラスター数
  for(int i=0;i<num;i++){
    std::cout << i << " " << component[i] << '\n';
  }
  
  return 0;
}
