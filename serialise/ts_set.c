#include <tina/all_tina.h>
#include <tina/cvr.h>
#include <tina/serialisefuncs.h>


Tina_data_info *tina_data_info_array;

void define_all_ts_handlers(void)
{
  tina_data_info_array = get_tina_data_info_array();		  

  TS_HANDLERS_SET(Matrix);
  TS_SWAP_STRING_SET(Matrix,"iiii,");

  TS_HANDLERS_SET(Edge_conn);
  
  TS_HANDLERS_SET(Vector);
  TS_SWAP_STRING_SET(Vector,"ii,");

  TS_SWAP_STRING_SET(Blk_stat,"up,uu");
  TS_SWAP_STRING_SET(Cmap_data_visible,"iiiii512iii256i");
  TS_SWAP_STRING_SET(Edge_fp,"w,");

  TS_HANDLERS_SET(Imrect);
  TS_SWAP_STRING_SET(Imrect,"iiip,p");

  TS_HANDLERS_SET(Rindex);
  TS_SWAP_STRING_SET(Rindex,"ip,");

  TS_HANDLERS_SET(Windex);
  TS_SWAP_STRING_SET(Windex,"iiip,");

  TS_HANDLERS_SET(List);
  TS_SWAP_STRING_SET(List,"iww");
  
  TS_HANDLERS_SET(Ddlist);
  TS_SWAP_STRING_SET(Ddlist,"iwww");
  
  TS_HANDLERS_SET(Prop);
  TS_SWAP_STRING_SET(Prop,"/type/i/count/i/freefunc/w,");
  
  TS_SWAP_STRING_SET(Line3,"/type/u/label/u/p1/t/p2/t/p/t/v/t/length/f/props/p")
    ;
  TS_SWAP_STRING_SET(Line2,"/type/u/label/u/p1/t/p2/t/p/t/v/t/length/f/props/p");

  TS_SWAP_STRING_SET(Pwrte_point_to_point,"/type1/i/type2/ipp/lowdist/f/highdist/f");
  TS_SWAP_STRING_SET(Pwrte_point_to_vec,
		     "/type1/i/type2/ipp/lowmind/f"
		     "/highmind/f/lowvecd/f/highvecd/f");
  TS_SWAP_STRING_SET(Pwrte_vec_to_vec,
		     "/type1/i/type2/ipp/lowang/f/hiang/f/lowmind/f/himind/f"
		     "/lowvec1/f/hivec1/f/lowvec2/f/hivec2/f");
  TS_SWAP_STRING_SET(Line2,"/type/u/label/u/p1end/t/p2end/t/p/t/v/t/length/f/props/p");
  TS_SWAP_STRING_SET(Line3,"/type/u/label/u/p1end/t/p2end/t/p/t/v/t/length/f/props/p");
  TS_SWAP_STRING_SET(Iso_error,"/rot/f/dot/f/pos/f");
  TS_SWAP_STRING_SET(Conic,"/type/u/label/ui/a/g/b/g/c/g/d/g/e/g/f/g/theta/g"
		     "/alpha/g/beta/g/center/ti/t1/g/t2/g/branch/i/props/p");
  TS_SWAP_STRING_SET(Conic3,"/type/i/conic/p/origin/t/ex/t/ey/t/ez/t");
}
