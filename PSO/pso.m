%Particle Swarm Optimization

clear
a = [1 2 3 4 5 6];

%ff = 'testfunctions'; % Objective Function
ff = 3;
% Initializing variables
popsize = 10; % Size of the swarm
npar = 2; % Dimension of the problem
maxit = 10; %100; % Maximum number of iterations
c1 = 1; % cognitive parameter
c2 = 4-c1; % social parameter
C=1; % constriction factor

% Initializing swarm and velocities
par=rand(popsize,npar); % random population of continuous values
% par = [1.9804 2.3333;
%        -1.1176 0.9216;
% -1.4314    2.9216;
%  3.5490   -2.8431;
% -0.4510    3.8235;
%  0.1765   -1.5882;
%  3.5490    3.1961;
%  0.8039    0.4902;
% -2.7647    0.0980;
% -0.2157   -4.6863];

vel = rand(popsize,npar); % random velocities

% Evaluate initial population
%cost=feval(ff,par); % calculates population cost using ff
cost=testfunctions(ff,par); % calculates population cost using ff
minc(1)=min(cost); % min cost
meanc(1)=mean(cost); % mean cost
globalmin=minc(1); % initialize global minimum

% Initialize local minimum for each particle
localpar = par; % location of local minima
localcost = cost; % cost of local minima

% Finding best particle in initial population
[globalcost,indx] = min(cost);
globalpar=par(indx,:);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Start iterations
iter = 0;    % counter

while iter < maxit
    iter = iter + 1;

% update velocity = vel
    w=(maxit-iter)/maxit; %inertia weiindxht
    r1 = rand(popsize,npar); % random numbers
    r2 = rand(popsize,npar); % random numbers
    vel = C*(w*vel + c1 *r1.*(localpar-par) + c2*r2.*(ones(popsize,1)*globalpar-par));

% update particle positions
par = par + vel; % updates particle position
overlimit=par<=1;
underlimit=par>=0;
par=par.*overlimit+not(overlimit);
par=par.*underlimit;

% Evaluate the new swarm
%cost = feval(ff,par); % evaluates cost of swarm
cost=testfunctions(ff,par); 

% Updating the best local position for each particle
bettercost = cost < localcost;
localcost = localcost.*not(bettercost) + cost.*bettercost;
localpar(find(bettercost),:) = par(find(bettercost),:);

% Updating index g
[temp, t] = min(localcost);
if temp<globalcost
globalpar=par(t,:); indx=t; globalcost=temp;
end
[iter globalpar globalcost] % print output each 
                            % iteration
minc(iter+1)=min(cost); % min for this 
                        % iteration
globalmin(iter+1)=globalcost; % best min so far
meanc(iter+1)=mean(cost); % avg. cost for
                          % this iteration

end% while

figure(24)
iters=0:length(minc)-1;
plot(iters,minc,iters,meanc,'–',iters,globalmin,':');
xlabel('generation');ylabel('cost');
text(0,minc(1),'best');text(1,minc(2),'population average')