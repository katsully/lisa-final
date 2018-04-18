
/*
This inline function was automatically generated using DecisionTreeToCpp Converter

It takes feature vector as single argument:
feature_vector[0] - Vector1
feature_vector[1] - Vector2
feature_vector[2] - Vector3
feature_vector[3] - Vector4
feature_vector[4] - Vector5


It returns index of predicted class:
0 - Hugging
1 - Hand Holding or other non-hugging touching


Simply include this file to your project and use it
*/

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include <vector>

using namespace ci;
using namespace ci::app;
using namespace std;

inline int kat_decision_tree(const std::vector<double> & feature_vector) 
{
	if (feature_vector.at(1) <= 0.38) {
		if (feature_vector.at(2) <= 0.56) {
			if (feature_vector.at(1) <= 0.37) {
				if (feature_vector.at(1) <= 0.36) {
					if (feature_vector.at(3) <= 0.57) {
						return 0;
					}
					else {
						if (feature_vector.at(3) <= 0.57) {
							return 1;
						}
						else {
							if (feature_vector.at(4) <= 0.62) {
								if (feature_vector.at(1) <= 0.31) {
									if (feature_vector.at(2) <= 0.16) {
										if (feature_vector.at(2) <= 0.16) {
											if (feature_vector.at(0) <= 0.37) {
												if (feature_vector.at(3) <= 0.62) {
													return 1;
												}
												else {
													return 0;
												}
											}
											else {
												if (feature_vector.at(2) <= 0.15) {
													return 0;
												}
												else {
													if (feature_vector.at(2) <= 0.15) {
														return 1;
													}
													else {
														return 0;
													}
												}
											}
										}
										else {
											return 1;
										}
									}
									else {
										return 0;
									}
								}
								else {
									if (feature_vector.at(1) <= 0.31) {
										return 1;
									}
									else {
										if (feature_vector.at(2) <= 0.37) {
											if (feature_vector.at(1) <= 0.35) {
												if (feature_vector.at(2) <= 0.11) {
													if (feature_vector.at(2) <= 0.11) {
														return 0;
													}
													else {
														return 1;
													}
												}
												else {
													return 0;
												}
											}
											else {
												if (feature_vector.at(1) <= 0.36) {
													return 1;
												}
												else {
													return 0;
												}
											}
										}
										else {
											if (feature_vector.at(0) <= 0.48) {
												return 1;
											}
											else {
												return 0;
											}
										}
									}
								}
							}
							else {
								if (feature_vector.at(0) <= 0.43) {
									if (feature_vector.at(3) <= 0.6) {
										return 1;
									}
									else {
										return 0;
									}
								}
								else {
									if (feature_vector.at(0) <= 0.53) {
										if (feature_vector.at(3) <= 0.62) {
											if (feature_vector.at(3) <= 0.61) {
												return 0;
											}
											else {
												return 1;
											}
										}
										else {
											return 0;
										}
									}
									else {
										if (feature_vector.at(2) <= 0.26) {
											return 0;
										}
										else {
											if (feature_vector.at(2) <= 0.36) {
												if (feature_vector.at(3) <= 0.6) {
													return 0;
												}
												else {
													if (feature_vector.at(4) <= 0.65) {
														return 1;
													}
													else {
														return 0;
													}
												}
											}
											else {
												return 0;
											}
										}
									}
								}
							}
						}
					}
				}
				else {
					if (feature_vector.at(1) <= 0.36) {
						if (feature_vector.at(4) <= 0.65) {
							return 1;
						}
						else {
							return 0;
						}
					}
					else {
						if (feature_vector.at(2) <= 0.22) {
							return 0;
						}
						else {
							if (feature_vector.at(3) <= 0.62) {
								return 0;
							}
							else {
								return 1;
							}
						}
					}
				}
			}
			else {
				if (feature_vector.at(4) <= 0.58) {
					if (feature_vector.at(4) <= 0.54) {
						return 0;
					}
					else {
						return 1;
					}
				}
				else {
					if (feature_vector.at(0) <= 0.59) {
						return 0;
					}
					else {
						if (feature_vector.at(3) <= 0.57) {
							return 1;
						}
						else {
							return 0;
						}
					}
				}
			}
		}
		else {
			if (feature_vector.at(4) <= 0.58) {
				if (feature_vector.at(0) <= 0.39) {
					return 1;
				}
				else {
					return 0;
				}
			}
			else {
				return 0;
			}
		}
	}
	else {
		if (feature_vector.at(0) <= 0.54) {
			if (feature_vector.at(4) <= 0.59) {
				if (feature_vector.at(1) <= 0.6) {
					if (feature_vector.at(1) <= 0.42) {
						if (feature_vector.at(3) <= 0.61) {
							if (feature_vector.at(3) <= 0.55) {
								if (feature_vector.at(0) <= 0.45) {
									if (feature_vector.at(0) <= 0.4) {
										return 1;
									}
									else {
										return 0;
									}
								}
								else {
									return 1;
								}
							}
							else {
								if (feature_vector.at(2) <= 0.16) {
									return 1;
								}
								else {
									if (feature_vector.at(0) <= 0.39) {
										return 1;
									}
									else {
										return 0;
									}
								}
							}
						}
						else {
							if (feature_vector.at(4) <= 0.53) {
								return 0;
							}
							else {
								return 1;
							}
						}
					}
					else {
						if (feature_vector.at(3) <= 0.55) {
							if (feature_vector.at(4) <= 0.54) {
								return 0;
							}
							else {
								if (feature_vector.at(3) <= 0.55) {
									return 1;
								}
								else {
									if (feature_vector.at(4) <= 0.58) {
										return 0;
									}
									else {
										return 1;
									}
								}
							}
						}
						else {
							if (feature_vector.at(2) <= 0.56) {
								if (feature_vector.at(4) <= 0.57) {
									if (feature_vector.at(4) <= 0.56) {
										return 0;
									}
									else {
										if (feature_vector.at(4) <= 0.56) {
											return 1;
										}
										else {
											if (feature_vector.at(2) <= 0.11) {
												if (feature_vector.at(3) <= 0.66) {
													return 1;
												}
												else {
													return 0;
												}
											}
											else {
												return 0;
											}
										}
									}
								}
								else {
									if (feature_vector.at(0) <= 0.44) {
										if (feature_vector.at(3) <= 0.66) {
											if (feature_vector.at(1) <= 0.42) {
												return 0;
											}
											else {
												if (feature_vector.at(2) <= 0.48) {
													return 1;
												}
												else {
													return 0;
												}
											}
										}
										else {
											return 0;
										}
									}
									else {
										if (feature_vector.at(0) <= 0.52) {
											if (feature_vector.at(1) <= 0.43) {
												return 1;
											}
											else {
												if (feature_vector.at(1) <= 0.54) {
													return 0;
												}
												else {
													if (feature_vector.at(2) <= 0.51) {
														return 1;
													}
													else {
														return 0;
													}
												}
											}
										}
										else {
											return 1;
										}
									}
								}
							}
							else {
								if (feature_vector.at(3) <= 0.57) {
									return 1;
								}
								else {
									return 0;
								}
							}
						}
					}
				}
				else {
					if (feature_vector.at(2) <= 0.11) {
						return 0;
					}
					else {
						if (feature_vector.at(4) <= 0.5) {
							if (feature_vector.at(2) <= 0.33) {
								return 1;
							}
							else {
								return 0;
							}
						}
						else {
							return 1;
						}
					}
				}
			}
			else {
				if (feature_vector.at(4) <= 0.65) {
					if (feature_vector.at(1) <= 0.4) {
						if (feature_vector.at(4) <= 0.64) {
							return 0;
						}
						else {
							return 1;
						}
					}
					else {
						if (feature_vector.at(0) <= 0.45) {
							if (feature_vector.at(0) <= 0.44) {
								if (feature_vector.at(2) <= 0.36) {
									return 0;
								}
								else {
									return 1;
								}
							}
							else {
								if (feature_vector.at(3) <= 0.55) {
									return 1;
								}
								else {
									return 0;
								}
							}
						}
						else {
							if (feature_vector.at(3) <= 0.49) {
								return 0;
							}
							else {
								if (feature_vector.at(2) <= 0.52) {
									if (feature_vector.at(2) <= 0.34) {
										if (feature_vector.at(3) <= 0.62) {
											if (feature_vector.at(0) <= 0.54) {
												return 0;
											}
											else {
												return 1;
											}
										}
										else {
											return 1;
										}
									}
									else {
										if (feature_vector.at(2) <= 0.49) {
											return 1;
										}
										else {
											if (feature_vector.at(1) <= 0.48) {
												return 0;
											}
											else {
												if (feature_vector.at(0) <= 0.54) {
													return 1;
												}
												else {
													if (feature_vector.at(3) <= 0.61) {
														return 0;
													}
													else {
														return 1;
													}
												}
											}
										}
									}
								}
								else {
									if (feature_vector.at(1) <= 0.58) {
										return 1;
									}
									else {
										return 0;
									}
								}
							}
						}
					}
				}
				else {
					return 0;
				}
			}
		}
		else {
			if (feature_vector.at(4) <= 0.51) {
				return 0;
			}
			else {
				if (feature_vector.at(1) <= 0.45) {
					if (feature_vector.at(3) <= 0.63) {
						if (feature_vector.at(2) <= 0.43) {
							return 0;
						}
						else {
							if (feature_vector.at(0) <= 0.66) {
								if (feature_vector.at(0) <= 0.61) {
									if (feature_vector.at(3) <= 0.57) {
										return 1;
									}
									else {
										return 0;
									}
								}
								else {
									return 1;
								}
							}
							else {
								return 0;
							}
						}
					}
					else {
						if (feature_vector.at(4) <= 0.59) {
							return 1;
						}
						else {
							return 0;
						}
					}
				}
				else {
					if (feature_vector.at(2) <= 0.12) {
						return 0;
					}
					else {
						if (feature_vector.at(4) <= 0.7) {
							if (feature_vector.at(0) <= 0.73) {
								if (feature_vector.at(3) <= 0.85) {
									if (feature_vector.at(1) <= 0.51) {
										if (feature_vector.at(4) <= 0.58) {
											return 1;
										}
										else {
											if (feature_vector.at(1) <= 0.49) {
												return 0;
											}
											else {
												if (feature_vector.at(2) <= 0.52) {
													if (feature_vector.at(1) <= 0.49) {
														return 1;
													}
													else {
														return 0;
													}
												}
												else {
													return 1;
												}
											}
										}
									}
									else {
										if (feature_vector.at(4) <= 0.6) {
											if (feature_vector.at(4) <= 0.6) {
												return 1;
											}
											else {
												return 0;
											}
										}
										else {
											return 1;
										}
									}
								}
								else {
									return 0;
								}
							}
							else {
								return 0;
							}
						}
						else {
							if (feature_vector.at(2) <= 0.82) {
								return 0;
							}
							else {
								return 1;
							}
						}
					}
				}
			}
		}
	}
}