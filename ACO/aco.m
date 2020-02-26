% ACO: ant colony optimization for solving the traveling salesperson problem

%Haupt & Haupt
%2003

clear
clc
rng(11) %rnd('state',11)
Ncity=30;       % number of cities on tour
Nants=Ncity;    % number of ants=number of cities

% city locations
xcity=rand(1,Ncity);ycity=rand(1,Ncity);   % cities are located at (xcity,ycity)

% distance between cities
for ic=1:Ncity
    for id=1:Ncity
        dcity(ic,id)=sqrt((xcity(ic)-xcity(id))^2+(ycity(ic)-ycity(id))^2);
    end % id
end % ic

vis=1./dcity                    % visibility equals inverse of distance
                                
phmone=.1*ones(Ncity,Ncity);    % initialized pheromones between cities
                                 
maxit= 1; %600;                      % max number of iterations

% a1=0 - closest city is selected
% be=0 - algorithm only works w/ pheromones and not distance of city
% Q - close to the lenght of the optimal tour
% rr - trail decay
a=2;b=6;rr=0.5;Q=sum(1./(1:8));dbest=9999999;e=5;

% initialize tours
for ic=1:Nants
    tour(ic,:)=randperm(Ncity);
end % ic
tour(:,Ncity+1)=tour(:,1);  % tour ends on city it starts with

for it=1:maxit
% find the city tour for each ant
% st is the current city
% nxt contains the remaining cities to be visited
    for ia=1:Nants
        for iq=2:Ncity-1
            [iq tour(ia,:)];
            st=tour(ia,iq-1); nxt=tour(ia,iq:Ncity);
            prob=((phmone(st,nxt).^a).*(vis(st,nxt).^b))
            sum((phmone(st,nxt).^a).*(vis(st,nxt).^b));
            rcity=rand;
            
            for iz=1:length(prob)
                if rcity<sum(prob(1:iz))
                    newcity=iq-1+iz;    % next city to be visited
                    break
                end    % if
            end     % iz
            
            temp=tour(ia,newcity);  % puts the new city selected next in line
            tour(ia,newcity)=tour(ia,iq);
            tour(ia,iq)=temp;
        end % iq
    end % ia
    
    % Calculate the lenght of each tour and pheromone distribution
    phtemp=zeros(Ncity,Ncity);
    for ic=1:Nants
        dist(ic,1)=0;
        for id=1:Ncity
            dist(ic,1)=dist(ic)+dcity(tour(ic,id),tour(ic,id+1));
            phtemp(tour(ic,id),tour(ic,id+1))=Q/dist(ic,1);
        end %id
    end % ic

    [dmin,ind]=min(dist);
    if dmin<dbest
        dbest=dmin;
    end % if

    % pheromone for elite path
    ph1=zeros(Ncity,Ncity);
    for id=1:Ncity
        ph1(tour(ind,id),tour(ind,id+1))=Q/dbest;
    end % id
    
    % update pheromone trails
    phmone=(1-rr)*phmone+phtemp+e*ph1;
    dd(it,:)=[dbest dmin];
    [it dmin dbest]
end % it

[tour,dist]
figure(1)
plot(xcity(tour(ind,:)),ycity(tour(ind,:)),xcity,ycity,'o')
axis square
figure(2);plot([1:maxit],dd(:,1),[1:maxit],dd(:,2),'-')