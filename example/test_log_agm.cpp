#include <chrono>
#include <limits>
#include <iomanip>
#include <iostream>

#include <boost/math/constants/constants.hpp>
#include <boost/multiprecision/cpp_bin_float.hpp>

namespace boost_gsoc2020
{
  template <class clock_type>
  struct stopwatch
  {
  public:
    typedef typename clock_type::duration duration_type;

    stopwatch() : m_start(clock_type::now()) { }

    stopwatch(const stopwatch& other) : m_start(other.m_start) { }

    stopwatch& operator=(const stopwatch& other)
    {
      m_start = other.m_start;
      return *this;
    }

    ~stopwatch() { }

    duration_type elapsed() const
    {
      return (clock_type::now() - m_start);
    }

    void reset()
    {
      m_start = clock_type::now();
    }

  private:
    typename clock_type::time_point m_start;
  };

  using big_float_type = boost::multiprecision::number<boost::multiprecision::cpp_bin_float<10000>,
                                                       boost::multiprecision::et_off>;

  using stopwatch_type = stopwatch<std::chrono::high_resolution_clock>;

  extern const std::string str_log_thirtyone_thirds_10k;
}

int main()
{
  const boost_gsoc2020::big_float_type dummy_ln2 = boost::math::constants::ln_two<boost_gsoc2020::big_float_type>();

  boost_gsoc2020::stopwatch_type my_stopwatch;

  boost_gsoc2020::big_float_type x = 10 + boost::math::constants::third<boost_gsoc2020::big_float_type>();

  // Compare with N[Log[31/3], 10000]
  my_stopwatch.reset();

  const boost_gsoc2020::big_float_type log_value = log(x);
  const boost_gsoc2020::big_float_type log_cntrl { boost_gsoc2020::str_log_thirtyone_thirds_10k };

  const auto execution_time =
    std::chrono::duration_cast<std::chrono::duration<float>>(my_stopwatch.elapsed()).count();

  std::cout << std::setprecision(std::numeric_limits<boost_gsoc2020::big_float_type>::digits10)
            << log_value
            << std::endl;

  std::cout << "execution_time: " << std::setprecision(3) << execution_time << "s" << std::endl;

  const boost_gsoc2020::big_float_type closeness = fabs(1 - fabs(log_value / log_cntrl));

  std::cout << "closeness: " << std::setprecision(3) << closeness << std::endl;
}

const std::string boost_gsoc2020::str_log_thirtyone_thirds_10k
{
  "2."
  "33537491581703655453391908761983150580244837265784252002202373883748712337894226534024907652235454178500690782308197907250253898842219317872406247839399304461710336144783484474948618307038591829917949406578730648941054507543135531056791199674207728977369241141108653304416446628688734774658226174430625585200396187028584914163096827019675975516047033541662890583239644905223533314657604242191848258897530664821214495591134343616962914567878088530148102303172651663772851034782904567315878639485090600986612188280176466487823145092796666181565515360653741636845988652048839808189204222966463691629899389666967038560704862400461906652965574467849270411213608257953557917419233037107256675459392363341568589376406137017429846275414796349512065280813209740642220326575303172278346231140160604632432341787553545044479197750946567060359039709010891118707160037098943992576682742507249290328144383937144618066126776009765191005368705301124671316166179561117076264805706553412276107968355915620488105176817636"
  "68385390732346737246700312385303544963131976233644870071607624473296111010950817724351932295989406787906127938864275944761866344853806679770097124101884029855063958000942021815498403153240234055137297003269749826399537927766065059856592389341924343451856121124141534684599522483068074228557217099065770115392732373806500535404445462788275805429433514679333163941394900505219166282911572955784431380164744873909261299801507081978731672409706294702342764478157297929609515767109931847209433619133444472337915291750309715201467667286056828358800442651207702086343073205248363085781474260397526909349860758882610062189794757061302267489781165873285567559941189166337902928876674360264499012306081879241870513317712246204722413854097773977478965848623291157032925421551871788924375594650182791931104187145639488706862941926154066831997112884951451608092243889201774853520300965263123619198152702773484172812251010448090384128303650385144791436688189608702016531269798642815075818980597459054418749676280917"
  "10685120717281026859476340052410152892521801859317076276194389860970585069679045673549174272500647492149086210271052423784013817023320865249318080991317199649495904848438024894926652185099309131778919303155639599461901033670410932477760949013971232876035160642405119198336466688678492110067847287628859775921884820994852688329173650693482297485551115748634207478642770122701431203211740454829412975187242138549686017999270413422151494227272979358575159164073108195731803610576064351214650418797450666120085392674315931628672071532113812054240102936742140555167525910827534165141123713806819829535381005474391808832522915300076480706414273320395321829327213079767468213110035127693612463725466319275228274482595366156242565456055735920723915526477134017382527095560503610897579927749039251073792376353456000785177650436827498559919294337780093135471556734795173184205753751530063706673341806908362919353883649636491353902557876340297127777559031036401586579949829114511988522760284718204964573961841675"
  "89990850429842950723039582434493350606324036192786188015674830483649560196406407159448795901443365080598185482510450623256314048159408982179773885636092083937982428926944607815033043265067806221930369941505661836340935849004196523273398677900315107955302895219010962658634226208939896828802154925904271310582081578945422312521357881735991810534593601248683136115674199227900553068909406466333480652927802180910356937863394963597011558246437348412811145434459072962713858559671655457232529732965807345014547820233907065786928992428866034951539383646525742361964573960684003218328753434328383076764143581919405887713878079870798211674472885755928867199019865700376575527722558049759465944011504242732706300037243919812561499108503218685105774091965374210401154487693563528753076884048512183393088175960699443391812504208580216312364032174995643642711601151061329813588004565481956618400854889576369280751736483770242352436584086134548487330216539346420529754349805642385402099476960589490165720442238250"
  "68830463820797091401527766770111226054859826339131717048093210989060405574598220126440213094902668501096718416863061135423977433211592223637991730186019917226405822320878289774429053902833338048926725215802861871845471849071769691571207689691415291009355573099514921892082125905446640318358797051534852729272831685590223701713872978338361547306694527364361256019452243620948955350606458478641911161216243672292381702001662687865589959187348062740503276719496616557153530356531295096937410020627298224208736616933732138352715344242020373934749389925534069856680037446306665721394960862797014706373499805802318459439273876360916168332500155387213780056122318185800568357771668461810602962735135320006719215775590371673897129104124633687856768454910853335984564528153194031633555091622726519519005584594391775254693371265760210183427961239790316387671768242050541204851415039512185164953310246627805850202650014998189783021953461375329301202688247107214096994835870606433730554169595935728004823324595779"
  "78210617499903915996677853765914853509817969670491285044145361420525480882401192191730831574506539837907845224858900647483518674096764059279799931981131474966037109370189957849153328878698908861548962830129675417173088272131688826128953773576440981777562803156478677874217563360306819088684512774410689279856061473501326632079863397821411384910658141798201734388669631108977537228707331443678160893704608799278823079196831759322409903053405180310260058347143108278220120908822254900377908896646342677326703523411316859401669125952313510330706855241456585752856972856383704331070775956379447602738940436314868015476782828071364602838012312293505212199788295123315667351202029423475935767340613198905879436100503421459619862088593982686382083576517621592695059907602451142071454895506089505468042461929900356145139858444440839237295635320380454692007947865737799111440756599732965746502494068018097470814790063758715844177651444549569265985479827283488373100818964852061848589839105691072287845226170532"
  "43319153376634126404020161008592204367484910415120969875010344683455857518864521757498489230673526202769667452929373125542995185318032758576529964612673377691922492917431063316477809631308911597085142121554247953587318127574514760086546176041991686280226373304727424562417202308269688511524937563988806332660704764430097571056191102604017811359725759081059614049827471620002680851071402404290414714314778664376740004985468066567596056491308220413921046240021586452996459967004717636322595924182274925673879457883697707976861368497880851150637294030826162481475322540881807269569709714727644839596967218447994014002356532780550244831567851729936517241819744521643157909962500299584852265275799156208335169182592365469105293998930811924597525215104881581121975049226500756606614630092265990056185753080432954511235668253051013794700865394750913423238619318358379413126379599299457368195362427811054003938407766727434778458793261660656054190877428426665880023296611982481293896890646426053692072012793756"
  "80276617742167598981255898955654242416211480158133208309447900272030484148012268963744255851704700108439366693439573422914615600487555494440343021179799526033959668589112258549943305425528719968838668772883925693083494993433141417316764329379857169966026034432163219654419045366262543337700193037687264166371786453983175897567929853419799064304627221342818770208037335496896968163428060971876302916286506112628327585812767943690667282339188389625544643882164695817081161669800273519506944720268404783082382215234506577753666149551955259258525843531047199897023309931536357427518023984481537473572313474116690051969656057674852677358278032722244429319163188635378145364549648114542557408489388009583008908904756158411032843688389708854522147351854401926946168407957581602087806479972531677431756314489080797136879512559914821902684130596168430941746788655057376167063338913887664483313973750823638962043553474547816786344002563284394733037169122366298047952202258707346080592506175703242008859732189061"
  "49584107729250646780703966172234840041526615394208512933005847603232546616348973749896241910892937011529995853694449595514860717083193904777314108797691236210501604347127717711690343008963941123203234039040466986538247860182056418261417013207592218780915587097424479970212080743292229893445196696717695378796152881384060618036524122001109963983298726399078593712709303961019117028737110063669725372001385752397856056828592790110501134435219662794729829078414102672951834345011613393764473694862559889345165874715752925137920163934768949270357458154683377692114440781570652845012226881244898800824738869363819479531521474277682191805489746389151575447106183596822590680231709292416394079961445438572281783704237140725323311865782428500318866705357431322249563365714821748881979537941912387768601124164562787962500471840178752117408245954665920311803243724937066402478624844853467332607506228450376507655229088024444152623048662248553575790788397539984632631380044664982943413994183965761468946896137080"
  "00621478029387863454924730253641992189001523535794876939494917278319553130436264101050590659767896958780432099435363925627932816501667512715795767693636522649341462776332105275860894177602928417646733719041877021583171492320198802734311521532793666415520937173337312941567455085441905124821149243708626061374663653782401427317855889125506066816351928764519642118327307146283781888479010324238725505631879549117171768934311923218413196377085698048683850389166260136988002725062553374503337430472616149831461135407065135657306798894513456054733527740794079015160992460059848661830843093169354476652969410788880356406923959663793034369874652009270006436774012709647328406376490196621066511810136849242304948951819887344053996904650358904120249824121329862246983546880086244469322090314391321231060046321589902897808577527244284078815708476405362673798882561128748504700793748642177445663794588388921627837973450891286775833809798450978894782532063619964257511500121384268062247172593467236206134720813632"
  "07"
};